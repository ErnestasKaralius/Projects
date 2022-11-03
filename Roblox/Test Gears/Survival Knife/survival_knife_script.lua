
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local Debris = game:GetService("Debris")

local tool = script.Parent
local handle = tool.Handle
local sparkles = handle.Sparkles

local weapon_hud = script.WeaponHud
local fill_bar = weapon_hud.Bar.Fill

local blood_part = script.Blood

local animations = { }
local sounds = {
	handle.Clash1, handle.Clash2, handle.Clash3, handle.Clash4, handle.Clash5,
	handle.Hit1, handle.Hit2, handle.Hit3,
	handle.Swoosh1, handle.Swoosh2
}

local deactivated = true
local can_be_blocked = true
local can_hit = false

local character
local current_animation

local swing_rate = 0.75
local damage = 22
local blood_effects = false

local random = math.random
local min = math.min
local pi = math.pi

function character_alive(character)
	if not character or not character:FindFirstChild("Humanoid") or character.Humanoid.Health <= 0 then return false end
	return true	
end

function find_character(parent)
	if parent and parent ~= workspace then
		local humanoid = parent:FindFirstChild("Humanoid")
		if humanoid then
			return parent, humanoid
		else
			return find_character(parent.Parent)
		end
	end
	return nil
end

function tag_humanoid(humanoid, player)
	for _, tag in pairs(humanoid:GetChildren()) do
		if tag and tag.Parent and tag.Name == "creator" then tag:Destroy() end
	end

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Name = "creator"
	creator_tag.Value = player
	Debris:AddItem(creator_tag, 1)
	creator_tag.Parent = humanoid
end

function has_same_team(character, player)
	local target_player = Players:GetPlayerFromCharacter(character)
	if not target_player then return false end

	local target_team = target_player.Team
	local creator_team = player.Team

	if not target_team or not creator_team or target_team ~= creator_team then return false end
	return true
end

function create_blood(limb)
	if not limb then return end

	local blood = blood_part:Clone()
	blood.CanTouch = true
	blood.Anchored = false
	blood.Transparency = random(0, 1) * 0.5
	blood.CanCollide = (random() < 0.5 and false) or true
	blood.Size = Vector3.new(0.2 * random(1, 5), 0.2 * random(1, 5), 0.2 * random(1, 5))
	blood.Velocity= limb.Velocity + Vector3.new(random() - 0.5, random() - 0.5, random() - 0.5) * 30
	blood.RotVelocity = limb.RotVelocity + Vector3.new(random() - 0.5, random() - 0.5, random() - 0.5) * 20
	blood.CFrame= limb.CFrame * CFrame.new((random() - 0.5) * 3, (random() - 0.5) * 3, (random() - 0.5) * 3) * CFrame.Angles(pi * 2 * random(), pi * 2 * random(), pi * 2 * random())
	Debris:AddItem(blood, random() * 4)
	blood.Parent = workspace
end

function create_billboard(position, text, lifetime, colour)
	local position = position or Vector3.new(0, 0, 0)
	local text = text or "Hello, World!"
	local lifetime = lifetime or 2
	local colour = colour or Color3.new(1, 0, 0)
	position += Vector3.new(0, 5, 0)

	local effect_part = blood_part:Clone()
	effect_part.Name = "Effect"
	effect_part.Size = Vector3.new(0, 0, 0)
	effect_part.CFrame=CFrame.new(position)
	effect_part.Anchored = true
	effect_part.CanCollide = false
	effect_part.Transparency = 1

	local billboard_gui = Instance.new("BillboardGui")
	billboard_gui.Size = UDim2.new(3, 0, 3, 0)
	billboard_gui.Adornee = effect_part

	local text_label = Instance.new("TextLabel")
	text_label.BackgroundTransparency = 1
	text_label.Size = UDim2.new(1, 0, 1, 0)
	text_label.Text = text
	text_label.TextColor3 = colour
	text_label.TextScaled = true
	text_label.Font = Enum.Font.ArialBold
	text_label.Parent = billboard_gui
	billboard_gui.Parent = effect_part

	Debris:AddItem(effect_part, lifetime + 0.1)
	effect_part.Parent = workspace

	task.spawn(function()
		local frames = lifetime * 60
		for frame=1, frames do
			task.wait()
			local per_cent = frame / frames
			effect_part.CFrame = CFrame.new(position) + Vector3.new(0, 5 * per_cent, 0)
			text_label.TextTransparency = per_cent
		end
		if effect_part and effect_part.Parent then effect_part:Destroy() end
	end)
end

function update_gui()
	tool.Enabled = false

	local cooldown_timer = 0
	while cooldown_timer < swing_rate do
		if not weapon_hud or weapon_hud.Parent == script then return end

		cooldown_timer += RunService.Heartbeat:Wait() / swing_rate
		local per_cent = min(cooldown_timer / swing_rate, 1)
		if per_cent < 0.5 then -- Fade from Red to Yellow to Green
			fill_bar.BackgroundColor3 = Color3.new(1, per_cent * 2, 0)
		else
			fill_bar.BackgroundColor3 = Color3.new(1 - (per_cent - 0.5) / 0.5, 1, 0)
		end
		fill_bar.Size = UDim2.new(per_cent, 0, 1, 0)
	end	

	tool.Enabled = true
end

handle.Touched:Connect(function(limb)
	if not limb or not limb.Parent or tool.Enabled or not character_alive(character) or not can_hit then return end
	
	local player = Players:GetPlayerFromCharacter(character)
	local target_character, target_humanoid = find_character(limb.Parent)
	if target_character == character or has_same_team(target_character, player) then return end
	can_hit = false

	if limb:FindFirstChild("CanBlock") and can_be_blocked then
		local clash_sound = sounds[random(1, 5)]
		clash_sound:Play()
		sparkles.Enabled = true

		task.delay(0.2, function()
			sparkles.Enabled = false
		end)

		create_billboard(handle.Position, "Block", 2, Color3.new(1, 1, 0))
	end
	
	if not character_alive(target_character) or target_character:FindFirstChildOfClass("ForceField") then return end

	tag_humanoid(target_humanoid, player)
	local hit_damage = math.floor(damage * (0.9 + random() * 0.2) + 0.5)
	target_humanoid:TakeDamage(hit_damage)

	create_billboard(limb.Position, ("-" .. tostring(hit_damage)))

	local hit_sound = sounds[random(6, 8)]
	hit_sound:Play()

	if not blood_effects then return end
	local blood_effect_amount = math.ceil(hit_damage / 10)
	for i=1, random(blood_effect_amount - 1, blood_effect_amount + 1) do
		create_blood(limb)
	end	
end)

tool.Activated:Connect(function()
	if not tool.Enabled then return end
	deactivated = false
	while not deactivated and character_alive(character) do
		local swoosh_sound = sounds[random(9, 10)]
		swoosh_sound:Play()

		local slash_animation = animations[random(2, 5)]
		while slash_animation == current_animation do
			slash_animation = animations[random(2, 5)]
		end
		slash_animation:Play()
		current_animation = slash_animation

		can_hit = true
		update_gui()
	end
end)

tool.Deactivated:Connect(function()
	deactivated = true
end)

tool.Equipped:Connect(function()
	character = tool.Parent
	local humanoid = character:FindFirstChild("Humanoid")
	if not character_alive(character) then return end

	local player = Players:GetPlayerFromCharacter(character)
	weapon_hud.Parent = player.PlayerGui

	local animator = humanoid:FindFirstChild("Animator")
	local animation_folder = script.R15
	if humanoid.RigType == Enum.HumanoidRigType.R6 then animation_folder = script.R6 end

	animations[1] = animator:LoadAnimation(animation_folder.Equip)
	animations[2] = animator:LoadAnimation(animation_folder.LeftSlash)
	animations[3] = animator:LoadAnimation(animation_folder.RightSlash)
	animations[4] = animator:LoadAnimation(animation_folder.Stab1)
	animations[5] = animator:LoadAnimation(animation_folder.Stab2)

	animations[1]:Play()

	update_gui()
end)

tool.Unequipped:Connect(function()
	if weapon_hud then weapon_hud.Parent = script end
	deactivated = true
	
	for _, animation in pairs(animations) do
		if animation then animation:Stop() end
	end
	for _, sound in pairs(sounds) do
		if sound then sound:Stop() end
	end
end)