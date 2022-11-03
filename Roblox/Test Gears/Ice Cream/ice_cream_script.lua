
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local tool = script.Parent

local icecream_effect_script = tool.IceCreamEffectScript

local lick_sound = tool.Handle.LickSound
local brain_freeze_gui = script.BrainFreezeGUI
local sugar_rush_gui = script.SugarRushGUI

local r6_lick_animation = script.R6LickAnimation
local r15_lick_animation = script.R15LickAnimation
local lick_animation

local increase = 1.25 -- 25% increase each successful lick
local sugar_rush_time = 10 -- How long the SugarRush effect will last

function create_icecream_variables(humanoid)
	local lick_amount = Instance.new("IntValue")
	lick_amount.Name = "IceCreamLickAmount"
	lick_amount.Parent = humanoid

	local last_lick = Instance.new("IntValue")
	last_lick.Name = "IceCreamLastLick"
	last_lick.Parent = humanoid

	local boost_level = Instance.new("IntValue")
	boost_level.Name = "IceCreamBoostLevel"
	boost_level.Parent = humanoid

	local boost_end_time = Instance.new("IntValue")
	boost_end_time.Name = "IceCreamBoostEndTime"
	boost_end_time.Parent = humanoid
	
	return lick_amount, last_lick, boost_level, boost_end_time
end

tool.Activated:Connect(function()
	local character = tool.Parent
	local humanoid = character:FindFirstChild("Humanoid")
	if not humanoid or humanoid.Health <= 0 then return end
	
	local player = Players:GetPlayerFromCharacter(character)
	local player_gui = player.PlayerGui
	
	-- Don't allow to use another Icecream gear while SugarCrash is in effect
	if player_gui:FindFirstChild("SugarCrashGUI") then return end
	
	-- These variables will be used by other IceCream gears
	local lick_amount, last_lick, boost_level, boost_end_time
	if humanoid:FindFirstChild("IceCreamLickAmount") then
		lick_amount = humanoid:FindFirstChild("IceCreamLickAmount")
		last_lick = humanoid:FindFirstChild("IceCreamLastLick")
		boost_level = humanoid:FindFirstChild("IceCreamBoostLevel")
		boost_end_time = humanoid:FindFirstChild("IceCreamBoostEndTime")
	else
		lick_amount, last_lick, boost_level, boost_end_time = create_icecream_variables(humanoid)
	end
	
	local animator = humanoid:FindFirstChild("Animator")
	if humanoid.RigType == Enum.HumanoidRigType.R15 then
		lick_animation = animator:LoadAnimation(r15_lick_animation)
	else
		lick_animation = animator:LoadAnimation(r6_lick_animation)
	end
	lick_animation:Play()
	
	lick_sound:Play()
	
	-- Brainfreeze
	if tick() - last_lick.Value < 2 then
		last_lick.Value = tick()
		humanoid:TakeDamage(30)
		
		-- We don't need copies of the same GUI
		if player_gui:FindFirstChild("BrainFreezeGUI") then return end
		
		local brain_freeze = brain_freeze_gui:Clone()
		Debris:AddItem(brain_freeze, 2)
		brain_freeze.Parent = player_gui
		
		return
	end
	lick_amount.Value += 1
	last_lick.Value = tick()
	
	-- Sugar Crash
	if math.random() > 1.5 / lick_amount.Value then
		local sugar_crash = sugar_rush_gui:Clone()
		sugar_crash.Name = "SugarCrashGUI"
		sugar_crash.Frame.SugarRushLabel.Text = "Sugar Crash!"
		Debris:AddItem(sugar_crash, 10)
		sugar_crash.Parent = player_gui
		
	-- Sugar Rush
	else
		humanoid.WalkSpeed *= increase
		boost_end_time.Value = time() + sugar_rush_time
		boost_level.Value += 1
		
		-- Run the while loop only once
		if player_gui:FindFirstChild("SugarRushGUI") then return end
		
		local sugar_rush = sugar_rush_gui:Clone()
		sugar_rush.Parent = player_gui
		
		local effect_script = icecream_effect_script:Clone()
		effect_script:SetAttribute("Increase", increase)
		effect_script.Disabled = false
		effect_script.Parent = character
	end
end)

tool.Unequipped:Connect(function()
	if lick_animation then lick_animation:Stop() end
end)
