
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ContextActionService = game:GetService("ContextActionService")
local UserInputService = game:GetService("UserInputService")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local explosive_statistics = require(ReplicatedStorage.Modules.ExplosiveStatistics)

local drive_event = ReplicatedStorage:WaitForChild("ControlVehicle")
local start_vehicle_event = ReplicatedStorage:WaitForChild("StartVehicle")

local scooter_stats = explosive_statistics.scooter
local controls = scooter_stats.controls

local player = Players.LocalPlayer

local character = player.Character
if not character or not character.Parent then character = player.CharacterAdded:Wait() end
local humanoid : Humanoid = character:WaitForChild("Humanoid")
local animator = humanoid:WaitForChild("Animator")

local animation_folder = (humanoid.RigType == Enum.HumanoidRigType.R15) and scooter_stats.animation_folder.R15 or scooter_stats.animation_folder.R6
local sit_animation = animator:LoadAnimation(animation_folder.Sit)

local tool = script.Parent

local jump_event

function control_vehicle(action, input_state)
	if input_state == Enum.UserInputState.Change then return end
	drive_event:FireServer(action, input_state == Enum.UserInputState.Begin and true or false)
end

tool.Equipped:Connect(function()
	if not gear_essentials.character_alive(humanoid) then return end
	
	ContextActionService:BindAction("Forward", control_vehicle, true, table.unpack(controls.accelerate))
	ContextActionService:SetPosition("Forward", UDim2.new(0.3, 0, 0.6, 0))
	ContextActionService:SetImage("Forward", "rbxassetid://2847847852")
	
	ContextActionService:BindAction("Backward", control_vehicle, true, table.unpack(controls.decelerate))
	ContextActionService:SetPosition("Backward", UDim2.new(0, 0, 0.6, 0))
	ContextActionService:SetImage("Backward", "rbxassetid://2847848304")
	
	ContextActionService:BindAction("Left", control_vehicle, true, table.unpack(controls.steer_left))
	ContextActionService:SetPosition("Left", UDim2.new(0, 0, 0.3, 0))
	ContextActionService:SetImage("Left", "rbxassetid://6993472329")
	
	ContextActionService:BindAction("Right", control_vehicle, true, table.unpack(controls.steer_right))
	ContextActionService:SetPosition("Right", UDim2.new(0.3, 0, 0.3, 0))
	ContextActionService:SetImage("Right", "rbxassetid://2418686949")
	
	ContextActionService:BindAction("Honk", control_vehicle, true, table.unpack(controls.honk))
	ContextActionService:SetPosition("Honk", UDim2.new(0.57, 0, 0.2, 0))
	ContextActionService:SetTitle("Honk", "Honk")
	
	jump_event = UserInputService.JumpRequest:Connect(function() 
		drive_event:FireServer("Jump", Enum.UserInputState.Begin) 
	end)

	sit_animation:Play()
	humanoid.PlatformStand = true
	
	start_vehicle_event:FireServer()
end)

tool.Unequipped:Connect(function()
	gear_essentials.unbind_actions("Forward", "Backward", "Left", "Right", "Honk")
	jump_event:Disconnect()
	
	if sit_animation then sit_animation:Stop() end
	humanoid.PlatformStand = false
end)