
local tool = script.Parent
local speed_up_sound = tool.Handle.SpeedUpSound
local smoke_trail = tool.Handle.Smoke

local speed_boost = 2 -- 100% speed increase
local speed_for_smoke = 10 -- smoke apears when character is running >= 10 studs/second

local humanoid
tool.Equipped:Connect(function()
	local character = tool.Parent
	humanoid = character:FindFirstChild("Humanoid")
	if not humanoid or humanoid.Health <= 0 then return end
	
	speed_up_sound:Play()
	humanoid.WalkSpeed *= speed_boost
	
	local humanoid_root = tool.Parent:FindFirstChild("HumanoidRootPart")
	if humanoid_root then
		smoke_trail.Attachment1 = humanoid_root:FindFirstChild("RootRigAttachment") 
		or humanoid_root:FindFirstChild("RootAttachment")
	end
	
	humanoid.Running:Connect(function(speed)
		if speed >= speed_for_smoke then
			smoke_trail.Enabled = true
			return
		end
		smoke_trail.Enabled = false
	end)
end)

tool.Unequipped:Connect(function()
	humanoid.WalkSpeed /= speed_boost
end)