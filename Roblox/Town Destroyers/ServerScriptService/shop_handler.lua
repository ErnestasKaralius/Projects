--!strict
local ServerStorage = game:GetService("ServerStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")

local shop_prices = require(ReplicatedStorage.Modules.ShopPrices)
local purchase_gear_function = ReplicatedStorage.PurchaseGear

local gear_folder = ServerStorage.Gears

purchase_gear_function.OnServerInvoke = function(player : Player, name : string) : boolean
	local leaderstats = player:FindFirstChild("leaderstats") :: Folder
	if not leaderstats then return false end
	
	local cash = leaderstats:FindFirstChild("Cash") :: IntValue
	if not cash then return false end
	
	local gear = gear_folder:FindFirstChild(name)
	if not gear then print("Gear " .. name .. " Not Found!") return false end
	
	local cost = shop_prices[name]
	if cash.Value < cost then return false end
	
	cash.Value -= cost
	_G.money_spent[tostring(player.UserId)] += cost
	
	gear = gear:Clone()
	gear.Parent = player:FindFirstChild("Backpack")
	
	return true
end



