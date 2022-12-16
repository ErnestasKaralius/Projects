--!strict
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local RunService = game:GetService("RunService")

local heartbeat = RunService.Heartbeat

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local explosive_statistics = require(ReplicatedStorage.Modules.ExplosiveStatistics)

local drive_event = ReplicatedStorage.ControlVehicle
local start_vehicle_event = ReplicatedStorage.StartVehicle

local scooter_stats = explosive_statistics.scooter
local controls = scooter_stats.controls

local scooter_body = ReplicatedStorage.Shared.ScooterBody

local engine_roar_sound = scooter_stats.engine_sound
local vehicle_honk_sound = scooter_stats.honk_sound

local max_speed = scooter_stats.max_speed
local speed_deceleration = scooter_stats.speed_deceleration
local max_rotation = scooter_stats.max_rotation
local speed_gain = scooter_stats.speed_gain
local rotation_gain = scooter_stats.rotation_gain

local jump_force = scooter_stats.jump_force
local jump_max_force = scooter_stats.jump_max_force
local jump_duration = scooter_stats.jump_duration
local jump_interval = scooter_stats.jump_interval

local max_smoke_opacity = scooter_stats.max_smoke_opacity
local opacity_increase_rate = scooter_stats.opacity_inrease_rate
local wheel_velocity_damper = scooter_stats.wheel_velocity_damper

function perform_jump(character : Model, thrust_force : BodyVelocity) : number
	thrust_force.MaxForce = Vector3.new(thrust_force.MaxForce.X, gear_essentials.get_object_mass(character) * workspace.Gravity * jump_max_force, thrust_force.MaxForce.Z)
	thrust_force.Velocity = Vector3.new(thrust_force.Velocity.X, jump_force, thrust_force.Velocity.Z)

	task.wait(jump_duration)

	thrust_force.MaxForce = Vector3.new(thrust_force.MaxForce.X, 0, thrust_force.MaxForce.Z)
	thrust_force.Velocity = Vector3.new(thrust_force.Velocity.X, 0, thrust_force.Velocity.Z)
	
	return tick()
end

function update_movement_speed(controls_status :{[string]: boolean}) : number
	if controls_status.Forward and controls_status.Backward then
		return 0
	end	
	if controls_status.Forward then
		return speed_gain
	end	
	if controls_status.Backward then
		return -speed_gain
	end
		
	return 0
end

function update_rotation_speed(controls_status :{[string]: boolean}) : number
	if controls_status.Left and controls_status.Right then
		return 0
	end
	if controls_status.Left then
		return rotation_gain
	end
	if controls_status.Right then
		return -rotation_gain
	end
	
	return 0	
end

function handle_rotation(current_rotation : number, rotation_force : BodyAngularVelocity, rotation_change : number) : number
	if math.abs(current_rotation) < max_rotation and rotation_change ~= 0 then
		rotation_force.AngularVelocity += Vector3.new(0, rotation_change, 0)
		current_rotation += rotation_change
	
	elseif current_rotation ~= 0 then
		local change = rotation_gain * -math.sign(current_rotation)
		current_rotation += change
		rotation_force.AngularVelocity += Vector3.new(0, change, 0)
	end
	
	return current_rotation
end

function handle_movement(current_speed : number, speed_change : number) : number
	if math.abs(current_speed) < max_speed and speed_change ~= 0 then
		current_speed += speed_change
	elseif current_speed ~= 0 then
		current_speed += speed_gain * -math.sign(current_speed) * speed_deceleration	
	end
	
	return current_speed
end

start_vehicle_event.OnServerEvent:Connect(function(player)
	local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
	if not gear_essentials.character_alive(humanoid) then return end
	
	local torso = character:FindFirstChild("Torso") :: Part or character:FindFirstChild("UpperTorso") :: Part
	local tool = character:FindFirstChildOfClass("Tool") :: Tool
	if not torso or not tool then return end
	
	local scooter = scooter_body:Clone()
	local front_motor = scooter.FrontMotor
	local back_motor = scooter.BackMotor
	local exaust_pipe = scooter.ExhaustPipe
	local motors = {scooter.FrontMotor, scooter.BackMotor}
	
	local engine_sound = engine_roar_sound:Clone()
	engine_sound.Parent = scooter
	local honk_sound = vehicle_honk_sound:Clone()
	honk_sound.Parent = scooter
	
	local current_rotation, current_speed = 0, 0
	local speed_change, rotation_change = 0, 0
	local last_jump = 0
	
	local rotation_force = scooter:FindFirstChild("BodyAngularVelocity")
	local thrust_force = scooter:FindFirstChild("BodyVelocity")
	
	scooter.Parent = tool
	engine_sound:Play()

	local torso_weld = Instance.new("Weld")
	torso_weld.C0 = CFrame.new(0, -0.75, -0.75)
	torso_weld.Part0 = torso
	torso_weld.Part1 = scooter
	torso_weld.Parent = scooter
	
	local controls_status :{[string]: boolean} = {
		["Forward"] = false,
		["Backward"] = false,
		["Left"] = false,
		["Right"] = false,
		["Jump"] = false,
		["Honk"] = false
	}
	
	local vehicle_drive_event
	vehicle_drive_event = drive_event.OnServerEvent:Connect(function(driving_player : Player, action : string, input_state : boolean)
		if driving_player ~= player or controls_status[action] == input_state then return end
		controls_status[action] = not controls_status[action]
		
		speed_change = update_movement_speed(controls_status)
		rotation_change = update_rotation_speed(controls_status)
	
		if controls_status.Honk and not honk_sound.IsPlaying then
			honk_sound:Play()
		end
		
		if controls_status.Jump and tick() - last_jump >= jump_interval then
			last_jump = perform_jump(character, thrust_force)
			controls_status.Jump = false
		end
	end)
	
	while scooter and scooter.Parent and gear_essentials.character_alive(humanoid) and gear_essentials.tool_equipped(tool) do
		
		current_speed = handle_movement(current_speed, speed_change)
		current_rotation = handle_rotation(current_rotation, rotation_force, rotation_change)
		
		-- Update Parameters
		local direction = torso.CFrame.LookVector
		local velocity = (direction * current_speed)
		thrust_force.Velocity = Vector3.new(velocity.X, thrust_force.Velocity.Y, velocity.Z)
		direction = Vector3.new(direction.X, 0, direction.Z).Unit
		
		for _, motor in pairs(motors) do
			motor.MaxVelocity = current_speed / wheel_velocity_damper
		end
		
		engine_sound.PlaybackSpeed = 1 + math.abs(current_speed / max_speed)
		exaust_pipe.ExhaustSmoke.Opacity = math.min(math.abs(current_speed), max_smoke_opacity) / opacity_increase_rate
		
		heartbeat:Wait()
	end
	
	scooter:Destroy()
	vehicle_drive_event:Disconnect()
end)