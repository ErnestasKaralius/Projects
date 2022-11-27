
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")
local RunService = game:GetService("RunService")

local explode_event = ServerStorage.Events.ExplodeEvent
local fuse_event = ServerStorage.Events.FuseEvent
local fire_event = ServerStorage.Events.FireEvent

local generic_explode_sound = ServerStorage.Shared.ExplodeSound
local generic_fuse_sound = ServerStorage.Shared.FuseSound

fire_event.Event:Connect(function(rocket, position_change, lifetime)
	local end_time = time() + lifetime
	while rocket and rocket.Parent and rocket.Transparency ~= 1 and time() < end_time do
		rocket.Position += position_change * RunService.Heartbeat:Wait()
	end
end)

fuse_event.Event:Connect(function(bomb, fuse_time, sound)
	local sparkles = Instance.new("Sparkles")
	sparkles.Parent = bomb
	
	local fuse_sound = sound and sound:Clone() or generic_fuse_sound:Clone()
	fuse_sound.Parent = bomb
	fuse_sound:Play()

	local explode_time = time() + fuse_time
	while time() < explode_time and RunService.Heartbeat:Wait() do
		sparkles.Color = Color3.new(1, 1 - time() / explode_time, 0)
	end
	
	fuse_sound:Destroy()
end)

explode_event.Event:Connect(function(player, bomb, blast_radius, blast_pressure, explode_time, sound)
	task.wait(explode_time)
	
	local explode_sound = sound and sound:Clone() or generic_explode_sound:Clone()
	explode_sound.Parent = bomb
	explode_sound:Play()
	
	local explosion = Instance.new("Explosion")
	explosion.Position = bomb.Position
	explosion.BlastRadius = blast_radius
	explosion.BlastPressure = blast_pressure
	explosion.Parent = workspace

	explosion.Hit:Connect(function(part)
		if part and part.Parent and part.Name ~= "Handle" and not part.Anchored and not part.Parent:FindFirstChild("Humanoid") then

			local has_active_welds = false
			for _, weld in pairs(part:GetChildren()) do
				if weld:IsA("WeldConstraint") and weld.Enabled then
					has_active_welds = true
					break
				end
			end

			if has_active_welds and player then
				local leaderstats = player:FindFirstChild("leaderstats")
				if leaderstats then leaderstats.Cash.Value += 1 end
			end
		end
	end)
	
	bomb.Anchored = true
	bomb.CanCollide = false
	bomb.CanTouch = false
	bomb.Transparency = 1
	
	Debris:AddItem(bomb)
end)

