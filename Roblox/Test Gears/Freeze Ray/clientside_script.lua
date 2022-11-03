
local Players = game:GetService("Players")
local player = Players.LocalPlayer
local mouse = player:GetMouse()

local tool = script.Parent
local fire_event = script:WaitForChild("Fire")

local character = player.Character
if not character or not character.Parent then character = player.CharacterAdded:Wait() end
local humanoid = character:WaitForChild("Humanoid")

local original_pos = tool.Grip
local fire_pos = CFrame.new(0.6, 0, -0.7, 0, -1, -0, -1, 0, -0, 0, 0, -1)

local reload_time = 5

tool.Activated:Connect(function()
	if not tool.Enabled or not character or not humanoid or humanoid.Health <= 0 then return end
	fire_event:FireServer(mouse.Hit.Position)
	
	tool.Enabled = false
	tool.Grip = fire_pos
	
	task.wait(reload_time)
	
	tool.Enabled = true
	tool.Grip = original_pos
end)