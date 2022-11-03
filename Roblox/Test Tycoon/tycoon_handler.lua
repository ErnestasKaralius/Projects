
local ServerStorage = game:GetService("ServerStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local MarketplaceService = game:GetService("MarketplaceService")

local purchase_stats = require(ReplicatedStorage.ModuleScripts.PurchaseStats)

local tycoon_stats = {}

local floor = math.floor
local ceil = math.ceil

function abbreviate_money(number)
	if number < 1000 then return floor(number) end

	local postfixes = {
		"", "K", "M", "B", "T", "Qa", "Qi", "Sx", "Sp",
		"Oc", "No", "Dc", "Ud", "Dd", "Td", "Qad", "Qid",
		"Sxd", "Spd", "Ocd", "Nod", "Vg", "Uvg", "Dvg",
		"Tvg", "Qavg", "Qivg", "Sxvg", "Spvg", "Ocvg"
	}

	local converted_number = string.format("%.0f", number)
	local digits = #converted_number

	local remaining = digits % 3
	if remaining == 0 then remaining = 3 end

	return string.sub(converted_number, 1, remaining) .. "." .. converted_number:sub(remaining+1, remaining+1) .. postfixes[ceil(digits / 3)]
end

function create_ore(dropper, statistics)
	local part_size = statistics.size
	local part_colour = statistics.colour
	local part_material = statistics.material
	local value = statistics.value
	
	local part = Instance.new("Part")
	part.Size = part_size
	part.Color = part_colour
	part.Material = part_material
	part.Position = dropper.Drop.Position
	part:SetAttribute("Value", value)
	part.Name = "Ore"
	
	return part
end

function change_laser_status(laser, button, fake_lasers, color, transparency, status)
	laser.CanTouch = status
	button.Color = color
	
	for _, fake_laser in pairs(fake_lasers) do
		fake_laser.Transparency = transparency
	end	
end

function character_alive(character)
	if character and character:FindFirstChild("Humanoid") and character.Humanoid.Health ~= 0 then return true end
	return false
end

function has_owner_status(player_name)
	for _, tycoon_stat in pairs(tycoon_stats) do
		if tycoon_stat.owner == player_name then return true end
	end
	return false
end

function hide_purchases(purchases)
	for _, purchase in pairs(purchases) do
		-- Reset the Lasers --
		local statistics = purchase_stats[purchase.Name]
		if statistics and statistics.laser then
			local laser = purchase.Laser
			local fake_lasers = purchase.Lasers:GetChildren()
			local button = purchase.Button.Press

			change_laser_status(laser, button, fake_lasers, Color3.fromRGB(58, 125, 21), 0, true)
		end
		purchase.Parent = nil
	end
end

function activate_purchases(tycoon_stats, ore_folder)
	local tycoon = tycoon_stats.tycoon
	for _, purchase in pairs(tycoon_stats.purchases) do
		local statistics = purchase_stats[purchase.Name]
		if not statistics then continue end
		-- Upgrader -- 
		if statistics.upgrader then
			local upgrade_part = purchase.Upgrade
			local value_boost = statistics.increase
			
			upgrade_part.Touched:Connect(function(part)
				if not part or not part.Parent or part.Parent.Name ~= "Ores" then return end
				
				local value = part:GetAttribute("Value") * value_boost
				part:SetAttribute("Value", value)
			end)
			
		-- Conveyor -- 
		elseif statistics.conveyor then
			local conveyor = purchase.Conveyor
			local speed = statistics.speed
			
			task.spawn(function()
				while RunService.Heartbeat:Wait() do
					conveyor.AssemblyLinearVelocity = conveyor.CFrame.LookVector * speed
				end
			end)
			
			-- Collector --
			if purchase:FindFirstChild("Collector") then
				local collector = purchase.Collector
				
				collector.Touched:Connect(function(part)
					if not part or not part.Parent or part.Parent ~= ore_folder then return end
					
					local player = Players:FindFirstChild(tycoon_stats.owner)
					local value = part:GetAttribute("Value")
					if not player or not value then return end
					
					tycoon_stats.money += value
					player.leaderstats.Money.Value = abbreviate_money(tycoon_stats.money)
					part:Destroy()
				end)
			end
		-- Laser --
		elseif statistics.laser then
			local laser = purchase.Laser
			local fake_lasers = purchase.Lasers:GetChildren()
			
			local button = purchase.Button.Press
			local click_detector : ClickDetector = button.ClickDetector
			
			laser.Touched:Connect(function(limb)
				local character = limb.Parent
				if not character_alive(character) or character.Name == tycoon_stats.owner then return end
			
				character.Humanoid.Health = 0
			end)
			
			click_detector.MouseClick:Connect(function(player)
				if player.Name ~= tycoon_stats.owner then return end
				
				if laser.CanTouch then
					change_laser_status(laser, button, fake_lasers, Color3.fromRGB(170, 0, 0), 0.75, false)
					return
				end	
				change_laser_status(laser, button, fake_lasers, Color3.fromRGB(58, 125, 21), 0, true)
			end)
		-- Duplicator --
		elseif statistics.duplicator then
			local click_detector : ClickDetector = purchase.Button.ClickDetector
			local part = create_ore(purchase, statistics)
			
			local cooldown = false
			click_detector.MouseClick:Connect(function()
				if cooldown then return end
				
				local ore = part:Clone()
				ore.Parent = ore_folder
				
				cooldown = true
				task.wait(0.5)
				cooldown = false
			end)
		-- Gear Giver --
		elseif statistics.giver then
			local button = purchase.Button
			local weapon = ServerStorage.Guns:FindFirstChild(statistics.weapon)
			
			local cooldown = false
			button.Touched:Connect(function(limb)
				local character = limb.Parent
				if cooldown or not character_alive(character) 
				or character.Name ~= tycoon_stats.owner then return end
				
				local player = Players:GetPlayerFromCharacter(character)
				local backpack = player.Backpack
				
				local gear = character:FindFirstChild(weapon.Name) or backpack:FindFirstChild(weapon.Name)
				if gear then
					gear.Parent = backpack
					gear:Destroy()
					local ammo_gui = player.PlayerGui:FindFirstChild("AmmoGUI")
					if ammo_gui then ammo_gui.Enabled = false end
				end
				
				gear = weapon:Clone()
				gear.Parent = backpack
				
				cooldown = true
				task.wait(1)
				cooldown = false
			end)
		end
	end
end

            

for i, tycoon in pairs(workspace.Tycoons:GetChildren()) do
	table.insert(tycoon_stats, {})
	tycoon_stats[i].tycoon = tycoon
	tycoon_stats[i].buttons = tycoon.Buttons:GetChildren()
	tycoon_stats[i].purchases = tycoon.Purchases:GetChildren()
	tycoon_stats[i].money = 1000000
	tycoon_stats[i].owner = ""
	
	local owner_door = tycoon.OwnerDoor.Door
	local owner_label = owner_door.OwnerGUI.OwnerLabel
	
	activate_purchases(tycoon_stats[i], tycoon.Ores)
	hide_purchases(tycoon_stats[i].purchases)
	
	-- Load in button functionality --
	for _, button in pairs(tycoon_stats[i].buttons) do
		local cost = purchase_stats[button.Name].cost
		local purchase_name = purchase_stats[button.Name].purchase
		local prerequisite = purchase_stats[button.Name].prerequisite
		
		if prerequisite ~= "" then button.Parent = nil end
		-- To ensure that you buy only once while checking for ownership
		local purchasing = false
		button.Touched:Connect(function(limb)
			local character = limb.Parent
			if purchasing or not character_alive(character) 
			or character.Name ~= tycoon_stats[i].owner then return end

			if tycoon_stats[i].money < cost then return end
			
			local player = Players:GetPlayerFromCharacter(character)
			local gamepass_id = purchase_stats[button.Name].gamepass
			
			purchasing = true
			if gamepass_id and not MarketplaceService:UserOwnsGamePassAsync(player.UserId, gamepass_id) then
				MarketplaceService:PromptGamePassPurchase(player, gamepass_id)
				return
			end
			purchasing = false
			
			tycoon_stats[i].money -= cost
			player.leaderstats.Money.Value = abbreviate_money(tycoon_stats[i].money)
			-- Show purchased object --
			for _, purchase in pairs(tycoon_stats[i].purchases) do
				if purchase.Name == purchase_name then
					purchase.Parent = tycoon.Purchases
					
					-- Activate the dropper if purchased
					local statistics = purchase_stats[purchase.Name]
					if statistics and statistics.dropper then
						local delay_time = 60 / statistics.rate
						local part = create_ore(purchase, statistics)
						
						task.spawn(function()
							while task.wait(delay_time) and purchase and purchase.Parent do	
								local ore = part:Clone()
								ore.Parent = tycoon.Ores
							end
						end)
					end
					break
				end
			end
			
			-- Show other buttons --
			for _, other_button in pairs(tycoon_stats[i].buttons) do
				if other_button.Parent or purchase_stats[other_button.Name].prerequisite ~= button.Name
				then continue end
					
				other_button.Parent = tycoon.Buttons
			end
		
			button.Parent = nil
		end)
	end
	
	owner_door.Touched:Connect(function(limb)
		if tycoon_stats[i].owner ~= "" then return end

		local character = limb.Parent
		if not character_alive(character) or has_owner_status(character.Name) then return end

		owner_label.Text = "Owner: " .. character.Name
		tycoon_stats[i].owner = character.Name
		
		local player = Players:GetPlayerFromCharacter(character)
		player.RespawnLocation = tycoon.TycoonSpawn
	end)
end

Players.PlayerAdded:Connect(function(player)
	local leaderstats = Instance.new("Folder")
	leaderstats.Name = "leaderstats"
	leaderstats.Parent = player

	local money = Instance.new("StringValue")
	money.Name = "Money"
	money.Value = "0"
	money.Parent = leaderstats
	
	player.RespawnLocation = workspace.Spawn
end)

Players.PlayerRemoving:Connect(function(player)
	for _, tycoon_stat in pairs(tycoon_stats) do
		local tycoon = tycoon_stat.tycoon
		if tycoon_stat.owner == player.Name then
			
			tycoon_stat.owner = ""
			tycoon.OwnerDoor.Door.OwnerGUI.OwnerLabel.Text = "Owner: None"
			tycoon_stat.money = 0
			
			-- Hide all purchases --
			hide_purchases(tycoon_stat.purchases)
			tycoon.Ores:ClearAllChildren()
			
			-- Hide all buttons besides starting ones --
			for _, button in pairs(tycoon_stat.buttons) do
				if purchase_stats[button.Name].prerequisite == "" then 
					button.Parent = tycoon.Buttons
				else
					button.Parent = nil
				end
			end
			
			break
		end
	end
end)