
local Players = game:GetService("Players")

local tool = script.Parent
local handle = tool.Handle

local throw_script = tool.ThrowScript

tool.Activated:Connect(function()
	local character = tool.Parent
	local humanoid = character:FindFirstChild("Humanoid")
	if not tool.Enabled or not humanoid or humanoid.Health <= 0 then return end
	
	local flashbang = handle:Clone()
	flashbang.Locked = true
	flashbang.Velocity = 60 * character.Head.CFrame.LookVector + Vector3.new(0, 30, 0)
	
	local tosser = Instance.new("ObjectValue")
	tosser.Value = Players:GetPlayerFromCharacter(character)
	tosser.Name = "Tosser"
	tosser.Parent = flashbang
	
	local activate_script = throw_script:Clone()
	activate_script.Disabled = false
	activate_script.Parent = flashbang
	flashbang.Parent = workspace

	handle.Transparency = 1
	tool.Enabled = false
	
	task.wait(14)
	
	handle.Transparency = 0
	tool.Enabled = true
end)
