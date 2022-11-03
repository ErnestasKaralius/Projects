
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local flashbang = script.Parent
local original_player = flashbang.Tosser.Value

local flashbang_gui = script.FlashGUI

local touch_event
touch_event = flashbang.Touched:Connect(function(part)
	local character = part.Parent
	if part.Name == "Handle" or character and character.Name == original_player.Name then return end
	
	flashbang.Transparency = 1
	flashbang.FlashSound:Play()
	touch_event:Disconnect()
	
	local affected_players = {}
	local players = Players:GetPlayers()
	
	for _, player in pairs(players) do
		if not player.Character then continue end
		
		local humanoid_root = player.Character.HumanoidRootPart
		if (humanoid_root.Position - flashbang.Position).Magnitude < 64 then
			table.insert(affected_players, player)
		end
	end
	
	for _, player in pairs(affected_players) do
		local flash_gui = flashbang_gui:Clone()
		flash_gui.Parent = player.PlayerGui
		flash_gui.BlindScript.OriginalPlayer.Value = original_player
		flash_gui.BlindScript.Disabled = false
	end
end)

Debris:AddItem(flashbang, 30)