
local ServerStorage = game:GetService("ServerStorage")
local BadgeService = game:GetService("BadgeService")
local GamePassService = game:GetService("GamePassService")
local Players = game:GetService("Players")

local gear_folder = ServerStorage.Gears

_G.admins = { 69164436, 73372997, 127573899, 2030850066, 311359998, 1294428855, 90865100, 1773636406 }

function give_badge(UserId, BadgeId)
	local success = pcall(function()
		return BadgeService:AwardBadge(UserId, BadgeId)
	end)
end

Players.PlayerAdded:Connect(function(player)

	local UserId = player.UserId
	
	local leaderstats = Instance.new("Folder")
	leaderstats.Name = "leaderstats"
	leaderstats.Parent = player
	
	local cash = Instance.new("IntValue")
	cash.Name = "Cash"
	cash.Value = 0
	cash.Parent = leaderstats
	
	if table.find(_G.admins, UserId) then
		cash.Value += 100000
	end
	if GamePassService:PlayerHasPass(player, 924615) then 
		cash.Value += 200
	end
	
	local old_value = cash.Value
	local total = 0
	local profit
	profit = cash.Changed:Connect(function(new_value)
		total += new_value - old_value
		if total >= 1000 then
			profit:Disconnect()
			give_badge(UserId, 2125995241)
		end
		old_value = new_value
	end)
	
	player.CharacterAppearanceLoaded:Connect(function()
		local gear
		-- EXTRA ROCKETS
		if GamePassService:PlayerHasPass(player, 923760) then 
			gear = gear_folder:FindFirstChild("BasicLauncher"):Clone()
			gear.Parent = player.Backpack
			
			gear = gear_folder:FindFirstChild("SuperLauncher"):Clone()
			gear.Parent = player.Backpack
			
			gear = gear_folder:FindFirstChild("ExponentialLauncher"):Clone()
			gear.Parent = player.Backpack
		end
		-- VIP
		if GamePassService:PlayerHasPass(player, 924615) then 
			gear = gear_folder:FindFirstChild("AccelerationCoil"):Clone()
			gear.Parent = player.Backpack
			
			gear = gear_folder:FindFirstChild("GravityCoil"):Clone()
			gear.Parent = player.Backpack
		end
		-- ADMIN GEARS
		if UserId == 69164436 then
			gear = gear_folder:FindFirstChild("GoldenBomb"):Clone()
			gear.Parent = player.Backpack			
		elseif UserId == 1294428855 then
			gear = gear_folder:FindFirstChild("HuTaoBomb"):Clone()
			gear.Parent = player.Backpack
		elseif UserId == 73372997 then
			gear = gear_folder:FindFirstChild("CrewmateTool"):Clone()
			gear.Parent = player.Backpack
		end
	end)
	give_badge(UserId, 2125524441)
end)
