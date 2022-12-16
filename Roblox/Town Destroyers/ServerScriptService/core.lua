
local Players = game:GetService("Players")
local ServerStorage = game:GetService("ServerStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local BadgeService = game:GetService("BadgeService")
local MarketplaceService = game:GetService("MarketplaceService")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local gear_folder = ServerStorage.Gears

local money_return_rate = 0.5
local admin_money_gain = 100_000
local vip_money_gain = 200

_G.admins = { 69164436, 73372997, 127573899, 2030850066, 311359998, 1294428855, 90865100, 1773636406 }
_G.money_spent = {}

function give_badge(UserId, BadgeId)
	local success = pcall(function()
		return BadgeService:AwardBadge(UserId, BadgeId)
	end)
end

Players.PlayerAdded:Connect(function(player : Player)
	local player_id = player.UserId
	local player_id_string = tostring(player_id)
	
	_G.money_spent[player_id_string] = 0
	
	local leaderstats = Instance.new("Folder")
	leaderstats.Name = "leaderstats"
	leaderstats.Parent = player
	
	local cash = Instance.new("IntValue")
	cash.Name = "Cash"
	cash.Value = 0
	cash.Parent = leaderstats
	
	if table.find(_G.admins, player_id) then
		cash.Value += admin_money_gain
	end
	
	if MarketplaceService:UserOwnsGamePassAsync(player_id, 924615) then 
		cash.Value += vip_money_gain
	end
	
	local old_value = cash.Value
	local total = 0
	local changed_event
	changed_event = cash.Changed:Connect(function(new_value)
		total += new_value - old_value
		if total >= 1000 then
			changed_event:Disconnect()
			give_badge(player_id, 2125995241)
		end
		old_value = new_value
	end)
	
	player.CharacterAdded:Connect(function()
		local backpack = player:FindFirstChild("Backpack") :: Folder
		local gear : Tool
		-- EXTRA ROCKETS
		if MarketplaceService:UserOwnsGamePassAsync(player_id, 923760) then 
			gear = gear_folder:FindFirstChild("BasicLauncher"):Clone()
			gear.Parent = backpack
			
			gear = gear_folder:FindFirstChild("SuperLauncher"):Clone()
			gear.Parent = backpack
			
			gear = gear_folder:FindFirstChild("ExponentialLauncher"):Clone()
			gear.Parent = backpack
		end
		-- VIP
		if MarketplaceService:UserOwnsGamePassAsync(player_id, 924615) then 
			gear = gear_folder:FindFirstChild("SpeedCoil"):Clone()
			gear.Parent = backpack
			
			gear = gear_folder:FindFirstChild("GravityCoil"):Clone()
			gear.Parent = backpack
		end
		-- ADMIN GEARS
		if player_id == 69164436 then
			gear = gear_folder:FindFirstChild("GoldenBomb"):Clone()
			gear.Parent = backpack		
		elseif player_id == 1294428855 then
			gear = gear_folder:FindFirstChild("HuTaoBomb"):Clone()
			gear.Parent = backpack
		elseif player_id == 73372997 then
			gear = gear_folder:FindFirstChild("CrewmateTool"):Clone()
			gear.Parent = backpack
		end
		
		local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
		local leaderstats = player:FindFirstChild("leaderstats") :: Folder
		local cash = leaderstats:FindFirstChild("Cash") :: IntValue
		
		humanoid.Died:Connect(function()
			if not cash then return end
			
			local spent_amount = _G.money_spent[player_id_string]
			if not spent_amount then return end
			
			cash.Value += math.round(spent_amount * money_return_rate)
			_G.money_spent[player_id_string] = 0
		end)
	end)
	give_badge(player_id, 2125524441)
	
end)

Players.PlayerRemoving:Connect(function(player)
	table.remove(_G.money_spent, table.find(_G.money_spent, tostring(player.UserId)))
end)
