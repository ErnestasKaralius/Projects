
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local explosive_stats = require(ReplicatedStorage.Modules.ExplosiveStatistics)

local fire_event = ServerStorage.Events.FireEvent
local get_mouse_pos = ReplicatedStorage.GetMousePos

local tool = script.Parent
local handle = tool.Handle

local mother_rocket = tool.MotherRocket
local exponential_launcher_rocket = ReplicatedStorage.Shared.ExponentialLauncherRocket

local rocket_stats = explosive_stats.exponential_rocket

local cooldown_time = rocket_stats.cooldown_time
local rocket_speed = rocket_stats.rocket_speed
local time_until_split = rocket_stats.time_until_split
local lifetime = rocket_stats.lifetime

local rocket_offsets = {
	Vector3.new(-3, 3, 0), Vector3.new(3, 3, 0), Vector3.new(0, -3, 0)
}

local character, humanoid, player

tool.Activated:Connect(function()
	if not tool.Enabled or not gear_essentials.character_alive(humanoid) then return end

	local target_pos = get_mouse_pos:InvokeClient(player)
	
	local rocket = exponential_launcher_rocket:Clone()
	rocket.CFrame = CFrame.lookAt(mother_rocket.Position, target_pos)
	
	local fire = rocket:FindFirstChild("Fire")
	fire.Enabled = true
	Debris:AddItem(fire, lifetime)
	
	rocket.Parent = workspace
	
	task.delay(time_until_split, function()
		if not rocket or not rocket.Parent or rocket.Transparency == 1 or not rocket:FindFirstChildOfClass("Fire") then return end
		for i = 1, #rocket_offsets do
			local new_rocket = exponential_launcher_rocket:Clone()
			new_rocket.CFrame = rocket.CFrame
			new_rocket.Position += rocket_offsets[i]
			new_rocket.Parent = workspace
			
			fire_event:Fire(player, new_rocket, rocket.CFrame.LookVector * rocket_speed, rocket_stats)
		end
	end)

	fire_event:Fire(player, rocket, rocket.CFrame.LookVector * rocket_speed, rocket_stats)

	tool.Enabled = false
	mother_rocket.Transparency = 1
	
	task.wait(cooldown_time)
	
	tool.Enabled = true
	mother_rocket.Transparency = 0
end)

tool.Equipped:Connect(function()
	character, humanoid, player = table.unpack(gear_essentials.get_player_components(tool))
end)