
local Players = game:GetService("Players")
local InsertService = game:GetService("InsertService")
local Debris = game:GetService("Debris")

local tool = script.Parent
local smoke_emitter = script.SmokeEmitter

local dummy_zombie = InsertService:LoadAsset(10947113402):FindFirstChildOfClass("Model")

local cooldown = 30
local zombies = 5
local spawn_distance = 15

local zombie_interval = 2

function create_zombie(position, player)
	local zombie = dummy_zombie:Clone()
	zombie.Owner.Value = player
	Debris:AddItem(zombie, cooldown)
	zombie.Parent = workspace
	zombie:MoveTo(position)
	
	task.spawn(function()
		task.wait(1)
		zombie.ZombieScript.Disabled = false
	end)
end

tool.Activated:Connect(function()
	local character = tool.Parent
	local player = Players:GetPlayerFromCharacter(character)
	local humanoid_root = character:FindFirstChild("HumanoidRootPart")
	local humanoid = character:FindFirstChild("Humanoid")
	if not tool.Enabled or not humanoid_root or not humanoid or humanoid.Health <= 0 then return end
	
	tool.GripPos = Vector3.new(0, 0.5, 0)
	tool.Enabled = false
	
	task.wait(0.5)
	tool.GripPos = Vector3.new(0, 0, 0)
	
	task.spawn(function()
		local emitter = smoke_emitter:Clone()
		emitter.Position = humanoid_root.Position + humanoid_root.CFrame.lookVector * spawn_distance
		emitter.Smoke.Enabled = true
		Debris:AddItem(emitter, 10)
		emitter.Parent = workspace
		
		task.wait(2)
		
		local remainder = zombies % 2
		local zombie_distance_x = zombie_interval
		local zombie_distance_y = zombie_interval
		
		if remainder == 1 then create_zombie(emitter.Position, player) end
		
		for i=1, zombies - remainder do
			create_zombie(emitter.Position + Vector3.new(zombie_distance_x, 0, zombie_distance_y), player)
			zombie_distance_y *= -1 -- The position only goes up and down
			
			if i % 2 == 0 then
				zombie_distance_x *= -1
				if zombie_distance_x < 0 then zombie_distance_x -= zombie_interval
				else zombie_distance_x += zombie_interval end
			end
		end
	end)
	
	task.wait(cooldown)
	tool.Enabled = true
end)