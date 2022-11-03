
local Players = game:GetService("Players")

local character = script.Parent
local humanoid = character:FindFirstChild("Humanoid")

local player = Players:GetPlayerFromCharacter(character)
local player_gui = player.PlayerGui

local boost_end_time = humanoid:FindFirstChild("IceCreamBoostEndTime")
local lick_amount = humanoid:FindFirstChild("IceCreamLickAmount")
local boost_level = humanoid:FindFirstChild("IceCreamBoostLevel")
local increase = script:GetAttribute("Increase")

function character_alive()
	if character and character:FindFirstChild("Humanoid") and character.Humanoid.Health ~= 0 then
		return true
	end
	return false
end

while character_alive() and time() < boost_end_time.Value 
	and not player_gui:FindFirstChild("BrainFreezeGUI") 
	and not player_gui:FindFirstChild("SugarCrashGUI") and task.wait() do 
end

humanoid.WalkSpeed /= increase ^ boost_level.Value
boost_level.Value = 0
lick_amount.Value = 0

local sugar_rush = player_gui:FindFirstChild("SugarRushGUI")
if sugar_rush then sugar_rush:Destroy() end

-- If Sugar Crash is the cause, temporarily lower the speed
if player_gui:FindFirstChild("SugarCrashGUI") then
	humanoid.WalkSpeed *= 0.75
	task.wait(10)
	humanoid.WalkSpeed /= 0.75
end

script:Destroy()