
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local tool = script.Parent
local handle = tool.Handle

local summon_sound = handle.SummonSound
local emerald_throw_script = tool.EmeraldScript

local r6_wave_animation = script.R6WaveAnimation
local r15_wave_animation = script.R15WaveAnimation

local emerald_amount = 7
local throw_speed = 75

local emeralds = {}
local dummy_emerald = script.Emerald

local wave_animation
local pi = math.pi

local cooldown = false

tool.Activated:Connect(function()
	local character = tool.Parent
	local humanoid = character:FindFirstChild("Humanoid")
	if cooldown or not character or not humanoid or humanoid.Health <= 0 then return end
	
	local torso = character:FindFirstChild("Torso") or character:FindFirstChild("UpperTorso")
	if not torso then return end
	
	local player = Players:GetPlayerFromCharacter(character)
	
	local animator = humanoid:FindFirstChild("Animator")
	if humanoid.RigType == Enum.HumanoidRigType.R15 then
		wave_animation = animator:LoadAnimation(r15_wave_animation)
	else
		wave_animation = animator:LoadAnimation(r6_wave_animation)
	end
	wave_animation:Play()
	summon_sound:Play()
	
	task.delay(0.5, function()
		if wave_animation then wave_animation:Stop() end
	end)
	
	local can_summon = true
	for _, emerald in ipairs(emeralds) do
		if emerald and emerald.Parent == workspace and emerald:FindFirstChild("Motor") then
			can_summon = false
			break
		end
	end
	
	if can_summon then
		for i=1, emerald_amount do
			local emerald = dummy_emerald:Clone()
			emerald.Anchored = false
			emerald.CanCollide = true
			emerald.CanTouch = true
			emerald.Transparency = 0.3
			
			local position_cframe = CFrame.new(0, 0, 0) * CFrame.Angles(0, ((i-1) / (emerald_amount - 1) - 0.5) * pi * 0.9, 0)
			* CFrame.new(0, 0, -5) * CFrame.Angles(0, pi * 0.5, pi * 0.5) * CFrame.Angles(0, pi * 0.25, 0)
			emerald.CFrame = torso.CFrame * position_cframe
			
			local motor = Instance.new("Motor")
			motor.Part0 = torso
			motor.Part1 = emerald
			motor.C0 = position_cframe
			motor.Parent = emerald
			
			local emerald_script = emerald_throw_script:Clone()
			emerald_script.Parent = emerald
			emerald_script.Disabled = false
			
			local creator_tag = emerald:FindFirstChild("creator")
			creator_tag.Value = player
			
			local fire = dummy_emerald:FindFirstChild("Fire")
			fire.Enabled = true
			
			task.delay(0.5, function()
				if fire then fire.Enabled = false end
			end)
			
			Debris:AddItem(emerald, 20)
			table.insert(emeralds, emerald)
			emerald.Parent = workspace
		end
	else
		for _, emerald in pairs(emeralds) do
			if emerald and emerald.Parent == workspace then
				emerald.VectorForce.Force = Vector3.new(0, workspace.Gravity * emerald:GetMass(), 0)
				
				local motor = emerald:FindFirstChild("Motor")
				local vector = (motor.Part1.Position - motor.Part0.Position).Unit
				motor:Destroy()
				
				emerald.CFrame=(emerald.CFrame + vector * 3) * CFrame.Angles(0, pi * 0.25, 0) * CFrame.Angles(pi * 0.5, 0, 0)
				emerald.Velocity = vector * throw_speed
				emerald.RotVelocity = Vector3.new(0, 50, 0)
				
				local fire = emerald:FindFirstChild("Fire")
				fire.Enabled = true
				task.delay(0.5, function()
					if fire then fire.Enabled = false end
				end)
						
			end
		end
		emeralds = {}
	end
	
	cooldown = true
	task.wait(2)
	cooldown = false
end)

tool.Unequipped:Connect(function()
	summon_sound:Stop()
	if wave_animation then wave_animation:Stop() end
end)

