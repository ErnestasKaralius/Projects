
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local tool = script.Parent
local handle = tool.Handle

local unsheath_sound = handle.UnsheathSound
local hit_sound = handle.HitSound
local swing_sound = handle.SwingSound

local r6_swing_animation = script.R6SwingAnimation
local r15_swing_animation = script.R15SwingAnimation
local swing_animation

local player = nil

local damage = 0
local slash_damage = 10

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

function tag_humanoid(humanoid)
	for _, tag in pairs(humanoid:GetChildren()) do
		if tag and tag.Parent and tag.Name == "creator" then tag:Destroy() end
	end

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Name = "creator"
	creator_tag.Value = player
	Debris:AddItem(creator_tag, 2)
	creator_tag.Parent = humanoid
end

function has_same_team(character)
	local target_player = Players:GetPlayerFromCharacter(character)
	if not target_player then return false end

	local target_team = target_player.Team
	local creator_team = player.Team

	if not target_team or not creator_team or target_team ~= creator_team then return false end
	return true
end

function create_body_force(limb, handle, force)
	local direction = (limb.Position - handle.Position).Unit
	local body_force = Instance.new("BodyForce")

	body_force.Force = direction * force
	body_force.Parent = limb
	Debris:AddItem(body_force, 0.5)	
end

handle.Touched:Connect(function(limb)
	if tool.Enabled or not limb or not limb.Parent or limb.Parent:FindFirstChildOfClass("ForceField") then return end
	
	local target_character, target_humanoid = find_character(limb.Parent)
	if target_character and target_character:FindFirstChildOfClass("ForceField") or target_character == character then return end
	
	if not hit_sound.IsPlaying then hit_sound:Play() end
	
	if not has_same_team(target_character) and target_humanoid and target_humanoid.Health ~= 0 then
		tag_humanoid(target_humanoid)
		target_humanoid:TakeDamage(damage)
		
		local torso = target_character:FindFirstChild("Torso") or target_character:FindFirstChild("UpperTorso") or limb
		create_body_force(torso, handle, 10000)
	else
		if limb:GetMass() < 34 then limb:BreakJoints() end
		create_body_force(limb, handle, 30000)
	end
end)

tool.Activated:Connect(function()
	local character = tool.Parent
	local humanoid = character:FindFirstChild("Humanoid")
	if not tool.Enabled or not humanoid or humanoid.Health <= 0 then return end
	player = Players:GetPlayerFromCharacter(character)
	tool.Enabled = false

	damage = slash_damage
	swing_sound:Play()
	
	local animator = humanoid:FindFirstChild("Animator")
	if humanoid.RigType == Enum.HumanoidRigType.R15 then
		swing_animation = animator:LoadAnimation(r15_swing_animation)
	else
		swing_animation = animator:LoadAnimation(r6_swing_animation)
	end
	swing_animation:Play()

	local end_time = time() + 2
	while time() < end_time and task.wait() do
		if not tool.Parent or not tool.Parent:FindFirstChild("Humanoid") or humanoid.Health <= 0 then break end
	end

	damage = 0
	tool.Enabled = true
end)

tool.Equipped:Connect(function()
	unsheath_sound:Play()
end)

tool.Unequipped:Connect(function()
	if swing_animation then swing_animation:Stop() end
	unsheath_sound:Stop()
	swing_sound:Stop()
end)


