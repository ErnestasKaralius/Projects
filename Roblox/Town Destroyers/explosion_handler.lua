
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")
local RunService = game:GetService("RunService")

local events_folder = ServerStorage.Events

local explode_event = events_folder.ExplodeEvent
local fuse_event = events_folder.FuseEvent
local fire_event = events_folder.FireEvent

function explode_bomb(player : Player, bomb : Part, bomb_stats)
	task.wait(bomb_stats.explode_time)

	local explode_sound = bomb_stats.explode_sound:Clone()
	explode_sound.Parent = bomb
	explode_sound:Play()

	local explosion = Instance.new("Explosion")
	explosion.Position = bomb.Position
	explosion.BlastRadius = bomb_stats.blast_radius
	explosion.BlastPressure = bomb_stats.blast_pressure
	explosion.ExplosionType = Enum.ExplosionType.NoCraters
	explosion.Parent = workspace

	explosion.Hit:Connect(function(part)
		if part and part.Parent and part.Name ~= "Handle" and not part.Anchored and not part.Parent:FindFirstChild("Humanoid") then
			
			for _, weld in pairs(part:GetChildren()) do
				if weld:IsA("WeldConstraint") and weld.Enabled then
					if player then
						local leaderstats = player:FindFirstChild("leaderstats")
						if leaderstats then leaderstats.Cash.Value += 1 end
					end
					break
				end
			end
		end
	end)

	bomb.Anchored = true
	bomb.CanCollide = false
	bomb.CanTouch = false
	bomb.Transparency = 1
	
	for _, part in pairs(bomb:GetChildren()) do
		if not part:IsA("SpecialMesh") and not part:IsA("Sound") then
			part:Destroy()
		end
	end

	Debris:AddItem(bomb)
end

fire_event.Event:Connect(function(player: Player, rocket : Part, position_change : Vector3, rocket_stats)
	rocket.Anchored = false
	
	local thrust_sound = rocket_stats.thrust_sound:Clone()
	thrust_sound.Parent = rocket
	thrust_sound:Play()

	local touched_event
	touched_event = rocket.Touched:Connect(function(part)
		if not part or not part.Parent or part:IsDescendantOf(player.Character) then return end
		
		touched_event:Disconnect()
		explode_bomb(player, rocket, rocket_stats)
	end)

	local end_time = time() + rocket_stats.lifetime
	while rocket and rocket.Parent and rocket.Transparency ~= 1 and time() < end_time do
		rocket.Position += position_change * RunService.Heartbeat:Wait()
	end
	
	if rocket and rocket.Transparency ~= 1 then rocket.Anchored = false end
	thrust_sound:Destroy()
end)

fuse_event.Event:Connect(function(player : Player, bomb : Part, bomb_stats)
	local sparkles = Instance.new("Sparkles")
	sparkles.Parent = bomb
	
	local fuse_sound = bomb_stats.fuse_sound:Clone()
	fuse_sound.Parent = bomb
	fuse_sound:Play()

	local explode_time = time() + bomb_stats.explode_time
	while time() < explode_time and RunService.Heartbeat:Wait() do
		sparkles.Color = Color3.new(1, 1 - time() / explode_time, 0)
	end
	
	fuse_sound:Destroy()
	explode_bomb(player, bomb, bomb_stats)
end)

explode_event.Event:Connect(explode_bomb)
