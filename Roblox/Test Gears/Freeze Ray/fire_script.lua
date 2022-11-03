
local tool = script.Parent
local handle = tool.Handle

local shoot_sound = handle.FireSound

local projectile = script.Projectile
local fire_event = tool.ActivateScript.Fire

local pellet_speed = 50

fire_event.OnServerEvent:Connect(function(player, target_pos)
	shoot_sound:Play()

	local pellet = projectile:Clone()
	pellet.CFrame = CFrame.lookAt(handle.Muzzle.WorldPosition, target_pos)
	pellet.Anchored = false
	pellet.CanTouch = true
	pellet.Transparency = 0.2
	pellet.LinearVelocity.VectorVelocity = pellet.CFrame.LookVector * pellet_speed
	
	local attachment = Instance.new("Attachment")
	pellet.LinearVelocity.Attachment0 = attachment
	attachment.Parent = pellet

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Value = player
	creator_tag.Name = "Creator"
	creator_tag.Parent = pellet
	
	pellet.ProjectileScript.Disabled = false
	pellet.Parent = workspace
end)

tool.Unequipped:Connect(function()
	shoot_sound:Stop()
end)