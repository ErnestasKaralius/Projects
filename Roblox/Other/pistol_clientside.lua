
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ContextActionService = game:GetService("ContextActionService")

local gear_essentials = require(ReplicatedStorage:WaitForChild("GearEssentials"))
local reload_event = script:WaitForChild("Reload")

local player = Players.LocalPlayer
local player_gui = player.PlayerGui

local character = player.Character
if not character or not character.Parent then character = player.CharacterAdded:Wait() end
local humanoid : Humanoid = character:WaitForChild("Humanoid")

local pistol = script.Parent

local ammo = pistol.GoldenPistolScript:WaitForChild("Ammo")
local clip_size = pistol.GoldenPistolScript:WaitForChild("ClipSize")

local ammo_gui = script:WaitForChild("AmmoGUI")
local ammo_text = ammo_gui.Ammunition:WaitForChild("AmmoCount")

ammo_text.TextSize = ammo_gui.Ammunition.AbsoluteSize.X * 0.3
ammo_text.Text = clip_size.Value .. "/" .. ammo.Value

local speed_increase = 1.5

function reload(action_name, input_state)
	if input_state == Enum.UserInputState.End or not gear_essentials.character_alive(humanoid) then return end
	
	reload_event:FireServer()
end

pistol.Equipped:Connect(function()
	ContextActionService:BindAction("Reload", reload, true, Enum.KeyCode.R, Enum.KeyCode.ButtonY)
	ContextActionService:SetPosition("Reload", UDim2.new(0.25, 0, 0.5, 0))
	ContextActionService:SetImage("Reload", "rbxassetid://7292214461")
	
	ammo_gui.Parent = player_gui
end)

pistol.Unequipped:Connect(function()
	ContextActionService:UnbindAction("Reload")
	
	if ammo_gui then ammo_gui.Parent = script end
end)

clip_size.Changed:Connect(function()
	ammo_text.Text = clip_size.Value .. "/" .. ammo.Value
end)