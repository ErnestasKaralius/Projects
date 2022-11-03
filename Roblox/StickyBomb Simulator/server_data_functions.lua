
local Players = game:GetService("Players")
local PhysicsService = game:GetService("PhysicsService")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")

local data_handler = require(ServerStorage.PlayerData)
local formulas = require(ReplicatedStorage.Modules.Formulas)

local request_data = ReplicatedStorage.Remotes.RequestData
local experience_changed = ReplicatedStorage.Remotes.ExperienceChanged
local new_level_reached = ReplicatedStorage.Remotes.NewLevelReached
local currency_changed = ReplicatedStorage.Remotes.CurrencyChanged
local request_language = ReplicatedStorage.Remotes.RequestLanguage

local pet_deleted = ReplicatedStorage.Remotes.PetDeleted
local pet_toggled = ReplicatedStorage.Remotes.PetToggled

local bomb_toggled = ReplicatedStorage.Remotes.BombToggled
local gear_folder = ServerStorage.Gears

local update_ui = ReplicatedStorage.Remotes.UpdateUI
local show_pets = ReplicatedStorage.Remotes.ShowPets

local data

Players.PlayerAdded:Connect(function(player)
	player.CharacterAdded:Connect(function(character)
		
		data = data_handler.get_data_by_player(player)

		data.coins = 0
		data.gems = 0
		data.xp = 0
		data.level = 0
		data.inventory_cap = 20
		data.equipped_pets = {}
		data.owned_pets = {  
			{id = "green_bob", is_equipped = false },
			{id = "yellow_bob", is_equipped = false },
			{id = "red_bob", is_equipped = false },
			{id = "green_bob", is_equipped = false },
			{id = "blue_bob", is_equipped = false },
			
		}
		data.equipped_bomb = "sticky_bomb"
		data.owned_bombs = {"sticky_bomb"}
		data.language = ""
		data.language = request_language:InvokeClient(player, data.language)
		
		add_tool(player)
		show_pets:FireAllClients(player, data.equipped_pets)
		
		while not player:HasAppearanceLoaded() do wait() end
		for _, limb in pairs(character:GetDescendants()) do
			if limb:IsA("BasePart") then
				PhysicsService:SetPartCollisionGroup(limb, "Players")
			end
		end
	end)
end)

function request_data.OnServerInvoke(player)
	return data_handler.get_data_by_player(player)
end

function _G.update_xp(player, new_xp)
	
	data.xp += new_xp

	local old_level = data.level
	local new_level = formulas.get_level(data.xp)
	
	if new_level > old_level then
		data.level = new_level
		new_level_reached:FireClient(player, data.level)
	end
	
	experience_changed:FireClient(player, old_level, new_level, data.xp)
end

function _G.update_currencies(player, coins, gems)

	data.coins += coins
	data.gems += gems
	
	currency_changed:FireClient(player, data.coins, data.gems)
end

function _G.add_pet(player, pet_id)
	
	if #data.owned_pets >= data.inventory_cap then
		return
	end
	
	table.insert(data.owned_pets, {id = pet_id, is_equipped = false})
	update_ui:FireClient(player, data)
end

pet_deleted.OnServerEvent:Connect(function(player, pet)
	
	if pet.is_equipped then
		table.remove(data.equipped_pets, table.find(data.equipped_pets, pet.id))
		show_pets:FireAllClients(player, data.equipped_pets)
	end
	
	table.remove(data.owned_pets, pet.index) -- Unlike equipped, must delete EXACTLY the one chosen
	update_ui:FireClient(player, data)
end)

pet_toggled.OnServerEvent:Connect(function(player, pet)
	
	if not pet.is_equipped then
		
		if #data.equipped_pets >= 4 then
			return
		end
	
		data.owned_pets[pet.index].is_equipped = true
		table.insert(data.equipped_pets, pet.id)
	else
		data.owned_pets[pet.index].is_equipped = false
		table.remove(data.equipped_pets, table.find(data.equipped_pets, pet.id))
	end
	update_ui:FireClient(player, data)
	show_pets:FireAllClients(player, data.equipped_pets)
end)

function _G.add_bomb(player, bomb)
	
	if table.find(data.owned_bombs, bomb) then
		return
	end
	
	table.insert(data.owned_bombs, bomb)
	sort_bombs(data.owned_bombs)
	update_ui:FireClient(player, data)
end

function sort_bombs(owned_bombs)
	table.sort(owned_bombs, function(a, b)
		if bomb_stats[a].Radius < bomb_stats[b].Radius then
			return true
		elseif bomb_stats[a].Radius == bomb_stats[b].Radius then
			return bomb_stats[a].ReloadTime < bomb_stats[b].ReloadTime
		end		
	end)
end

bomb_toggled.OnServerEvent:Connect(function(player, bomb)
	
	if bomb ~= data.equipped_bomb then
		delete_tool(player)
		data.equipped_bomb = bomb
		add_tool(player)
	else
		delete_tool(player)
	end
	
	update_ui:FireClient(player, data)
end)

function delete_tool(player)

	player.StarterGear:ClearAllChildren()
	player.Backpack:ClearAllChildren()
	data.equipped_bomb = ""

	if not player.Character then
		return
	end

	local tool = player.Character:FindFirstChildOfClass("Tool")
	if tool then
		tool:Destroy()
	end
end

function add_tool(player)
	
	if data.equipped_bomb == "" or player.StarterGear:FindFirstChildOfClass("Tool") then
		return
	end
	
	local tool_1 = gear_folder:FindFirstChild(data.equipped_bomb):Clone()
	local tool_2 = gear_folder:FindFirstChild(data.equipped_bomb):Clone()
	tool_1.Parent = player.StarterGear
	tool_2.Parent = player.Backpack	
end


