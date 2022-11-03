
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local request_data = ReplicatedStorage.Remotes.RequestData

local pet_inventory = script.Parent

local update_ui = ReplicatedStorage.Remotes.UpdateUI
local pet_deleted = ReplicatedStorage.Remotes.PetDeleted
local pet_toggled = ReplicatedStorage.Remotes.PetToggled

local formulas = require(ReplicatedStorage.Modules.Formulas)
local pet_stats = require(ReplicatedStorage.Modules.PetStats)
local languages = require(ReplicatedStorage.Modules.Languages)

local statistics = pet_inventory.Statistics
local stat_categories = { "XP", "Coins", "Radius", "Reload" }

local inventory = pet_inventory.Grid
local slot_template = script.SlotTemplate
local slots

function assign_indexes(owned_pets)
	
	for index, pet in ipairs(owned_pets) do
		-- Index pinpoints the location in Server Data
		pet.index = index
	end	
end

-- Load data
local latest_data = request_data:InvokeServer()
assign_indexes(latest_data.owned_pets)

--- Toggle Delete Mode
local delete_button = pet_inventory.Options.Delete
local delete_mode = false

delete_button.Activated:Connect(function()
	
	if delete_mode then
		delete_mode = false
		print("Delete mode OFF")
	else
		delete_mode = true
		print("Delete mode ON")
	end
end)

-- Sorting
local category = "rarity"
local order = "descending"

local sort_by_name = pet_inventory.Options.Sort:FindFirstChild("Name")
local sort_by_rarity = pet_inventory.Options.Sort.Rarity
local sort_label = pet_inventory.Options.Sort.SortLabel

sort_by_name.Text = languages[_G.language].sort_name
sort_by_rarity.Text = languages[_G.language].sort_rarity
sort_label.Text = languages[_G.language].sort_by

local sort_categories = {
	sort_by_name,
	sort_by_rarity
}

local rarities = {
	["Common"] = 5,
	["Uncommon"] = 4,
	["Rare"] = 3,
	["Epic"] = 2,
	["Legendary"] = 1
}

for _, sort in pairs(sort_categories) do
	local ascending = false

	sort.Activated:Connect(function()
		category = sort.Name:lower()

		if ascending then
			ascending = false
			order = "descending"
		else
			ascending = true
			order = "ascending"
		end
		formulas.clear_inventory_slots(slots)
		update_pets(latest_data)
	end)
end

function sort_pets(owned_pets)
	local comparisons = {
		["rarity"] = {
			["ascending"] = function(a, b)
				if rarities[pet_stats[a.id].Rarity] > rarities[pet_stats[b.id].Rarity] then
					return true
				elseif rarities[pet_stats[a.id].Rarity] == rarities[pet_stats[b.id].Rarity] then
					return languages[_G.language][a.id] < languages[_G.language][b.id]
				end
			end,
			["descending"] = function(a, b) 
				if rarities[pet_stats[a.id].Rarity] < rarities[pet_stats[b.id].Rarity] then
					return true
				elseif rarities[pet_stats[a.id].Rarity] == rarities[pet_stats[b.id].Rarity] then
					return languages[_G.language][a.id] < languages[_G.language][b.id]
				end		
			end,
		},
		["name"] = {
			["ascending"] = function(a, b)
				return languages[_G.language][a.id] > languages[_G.language][b.id]		
			end,
			["descending"] = function(a, b)
				return languages[_G.language][a.id] < languages[_G.language][b.id]
			end,			
		}
	}
	table.sort(owned_pets, comparisons[category][order])
end

-- Update on New/Deleted Item
update_ui.OnClientEvent:Connect(function(data)
	
	formulas.clear_inventory_slots(slots)
	assign_indexes(data.owned_pets)
	latest_data = data
	update_pets(data)
end)

function update_pets(data)
	-- Fill up grid with empty slots
	for i=1, data.inventory_cap do
		local slot = slot_template:Clone()
		slot.Parent = inventory		
	end
	
	sort_pets(data.owned_pets)

	-- Add Items to slots
	slots = inventory:GetChildren()
	for index, pet in ipairs(data.owned_pets) do
		local pet_id = pet.id
		local slot = slots[index + 2] -- Frames start from 3
		slot.Image = pet_stats[pet_id].Texture
		
		if pet.is_equipped then
			slot.ImageTransparency = 0.5
		end
		
		slot.MouseEnter:Connect(function()
			
			statistics.ItemName.Text = languages[_G.language][pet_id]
			statistics.Description.Text = languages[_G.language][pet_id .. "_desc"]
			statistics.Radius.Text = languages[_G.language].stat_radius .. formulas.convert_to_percentage(pet_stats[pet_id].Boosts.Radius)
			statistics.Coins.Text = "$: " .. formulas.convert_to_percentage(pet_stats[pet_id].Boosts.Coins)
			statistics.Reload.Text = languages[_G.language].stat_reload .. formulas.convert_to_percentage(pet_stats[pet_id].Boosts.Reload)
			statistics.XP.Text = languages[_G.language].stat_experience .. formulas.convert_to_percentage(pet_stats[pet_id].Boosts.XP)
			
			-- Remove categories which do not give buffs
			for _, stat in pairs(stat_categories) do
				if pet_stats[pet_id].Boosts[stat] == 1 then
					statistics[stat].Visible = false
				else
					statistics[stat].Visible = true
				end
			end
		end)
		
		slot.Activated:Connect(function()
			
			if delete_mode then
				pet_deleted:FireServer(pet)
				return
			end
			
			if not pet.is_equipped and #data.equipped_pets >= 4 then
				return
			end
			
			pet_toggled:FireServer(pet)
		end)
	end	
end

update_pets(latest_data)