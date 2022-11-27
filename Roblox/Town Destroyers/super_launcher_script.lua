
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")

local gear_essentials = require(ReplicatedStorage.GearEssentials)

local get_mouse_pos = ReplicatedStorage.GetMousePos
local fire_event = ServerStorage.Events.FireEvent
local explode_event = ServerStorage.Events.ExplodeEvent

local tool = script.Parent
local handle = tool.Handle

local super_launcher_rocket = ServerStorage.Shared:FindFirstChild("SuperLauncherRocket")

local launch_sound = handle.LaunchSound
local reload_sound = handle.ReloadSound
local explode_sound = ServerStorage.Shared.SuperLauncherExplodeSound

local reload_animation
local animation

local character, humanoid, animator, player

local rocket_amount = 5
local rocket_speed = 50
local dive_speed = 100
local lifetime = 15

local rocket_spread = 6
local rocket_offsets = {
	Vector3.new(0, 0, 0),
	Vector3.new(rocket_spread, 0, 0), Vector3.new(0, 0, rocket_spread),
	Vector3.new(-rocket_spread, 0, 0), Vector3.new(0, 0, -rocket_spread)
}

function reload_rockets()
	for i = 1, rocket_amount do
		if gear_essentials.tool_equipped(tool) then
			reload_sound:Play()
			reload_animation:Play()

			local new_rocket = super_launcher_rocket:Clone()
			new_rocket:FindFirstChild("Fire"):Destroy()

			local left_arm = character:FindFirstChild("Left Arm") or character:FindFirstChild("LeftHand")
			if left_arm then
				new_rocket.CFrame = left_arm:FindFirstChild("LeftGripAttachment").WorldCFrame * CFrame.new(0, 0, -0.5)

				local weld = Instance.new("WeldConstraint")
				weld.Part0 = left_arm
				weld.Part1 = new_rocket
				weld.Parent = new_rocket
				Debris:AddItem(new_rocket, reload_animation.Length * 0.7)
				new_rocket.Parent = character
			end
			task.wait(reload_animation.Length)
			reload_sound:Stop()
		end
	end
	tool.Enabled = true	
end

function launch_rocket(target_pos)
	task.spawn(function()
		launch_sound:Play()
		
		local rocket = super_launcher_rocket:Clone()
		rocket.Position = handle.Muzzle.WorldPosition
		Debris:AddItem(rocket, lifetime)
		rocket.Parent = workspace
		rocket:FindFirstChild("ThrustSound"):Play()
		
		fire_event:Fire(rocket, rocket.CFrame.LookVector * rocket_speed, 1.5)
		
		task.delay(1.5, function()
			rocket.CFrame = CFrame.lookAt(rocket.Position, target_pos)
			fire_event:Fire(rocket, rocket.CFrame.LookVector * dive_speed, lifetime)
		end)
		
		local touched_event
		touched_event = rocket.Touched:Connect(function(part)
			if not part or not part.Parent or part:IsDescendantOf(character) then return end

			explode_event:Fire(player, rocket, 4, 500000, 0, explode_sound)
			rocket:FindFirstChild("Fire").Enabled = false
			rocket:FindFirstChild("ThrustSound"):Destroy()
			touched_event:Disconnect()
		end)
	end)
end

tool.Activated:Connect(function()
	if not tool.Enabled or not gear_essentials.character_alive(humanoid) then return end
	tool.Enabled = false
	
	local mouse_pos = get_mouse_pos:InvokeClient(player)
	
	for i = 1, rocket_amount do
		if gear_essentials.tool_equipped(tool) then 
			launch_rocket(mouse_pos) 
		end
		task.wait(0.2)
	end
	
	task.wait(0.25)
	reload_rockets()
end)

tool.Equipped:Connect(function()
	character = tool.Parent
	humanoid = character:FindFirstChild("Humanoid")
	animator = humanoid:FindFirstChild("Animator")
	player = Players:GetPlayerFromCharacter(character)
	reload_animation = animator:LoadAnimation((humanoid.RigType == Enum.HumanoidRigType.R15) and script.R15ReloadAnimation or script.R6ReloadAnimation)
end)

tool.Unequipped:Connect(function()
	if reload_animation then reload_animation:Stop() end
end)