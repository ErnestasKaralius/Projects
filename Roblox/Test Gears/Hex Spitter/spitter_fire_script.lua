
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local tool = script.Parent
local handle = tool.Handle

local fire_sound = handle.FireSound
local empty_mag_sound = handle.EmptyMagSound

local fire_remote_function = tool.ActivateScript.Fire

local laser = script.Laser
local light = handle.Light

local raycast_params = RaycastParams.new()
raycast_params.FilterType = Enum.RaycastFilterType.Blacklist

local offset = Vector3.new(1, 1, 1) * 100
local accuracy = Vector3.new(0.5, 0.5, 0.5) * 100
local range = 100
local damage = 13

local random = math.random
local min = math.min
local max = math.max

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

function create_laser(muzzle_pos, target_pos)
	target_pos += Vector3.new(random(-offset.X, offset.X) * 0.01, random(-offset.Y, offset.Y) * 0.01, random(-offset.Z, offset.Z) * 0.01)
	target_pos += Vector3.new(random(-accuracy.X, accuracy.X) * 0.01, random(-accuracy.Y, accuracy.Y) * 0.01, random(-accuracy.Z, accuracy.Z) * 0.01)
	
	local vector = target_pos - muzzle_pos
	local distance = vector.Magnitude
	local direction = vector.Unit

	local PX = muzzle_pos + 0.25 * distance * direction
	local PY = muzzle_pos + 0.5 * distance * direction
	local PZ = muzzle_pos + 0.75 * distance * direction

	local DX = (muzzle_pos - PX).Magnitude
	local DY = (PX - PY).Magnitude
	local DZ = (PY - PZ).Magnitude

	local limit = 2
	local AX = PX + Vector3.new(random(max(-limit, -0.21 * DX), min(limit, 0.21 * DX)), random(max(-limit, -0.21 * DX), min(limit, 0.21 * DX)), random(max(-limit, -0.21 * DX), min(limit, 0.21 * DX)))
	local AY = PY + Vector3.new(random(max(-limit, -0.21 * DY), min(limit, 0.21 * DY)), random(max(-limit, -0.21 * DY), min(limit, 0.21 * DY)), random(max(-limit, -0.21 * DY), min(limit, 0.21 * DY)))
	local AZ = PZ + Vector3.new(random(max(-limit, -0.21 * DZ), min(limit, 0.21 * DZ)), random(max(-limit, -0.21 * DZ), min(limit, 0.21 * DZ)), random(max(-limit, -0.21 * DZ), min(limit, 0.21 * DZ)))

	local rays = {
		{distance = (AX - muzzle_pos).Magnitude, direction = CFrame.new(muzzle_pos, AX)},
		{distance = (AY - AX).Magnitude, direction = CFrame.new(AX, AY)},
		{distance = (AZ - AY).Magnitude, direction = CFrame.new(AY, AZ)},
		{distance = (target_pos - AZ).Magnitude, direction = CFrame.new(AZ, target_pos)}
	}

	for i, ray in pairs(rays) do
		local beam = laser:Clone()
		beam.Transparency = 0.7
		
		local mesh = beam.Mesh
		mesh.Scale = Vector3.new(0.15, 0.15, ray.distance) * 5
		beam.CFrame = ray.direction * CFrame.new(0, 0, -0.5 * ray.distance)
		Debris:AddItem(beam, 0.1 / (#rays - (i - 1)))
		beam.Parent = workspace
	end
end

fire_remote_function.OnServerInvoke = function(player, target_pos, muzzle_pos, clip_size)
	if clip_size <= 0 then empty_mag_sound:Play() return false end
	
	fire_sound:Play()
	if not light.Enabled then
		light.Enabled = true
		task.delay(0.1, function()
			light.Enabled = false
		end)
	end
	
	local direction = (target_pos - muzzle_pos).Unit * range
	raycast_params.FilterDescendantsInstances = {player.Character}
	
	local raycast_result = workspace:Raycast(muzzle_pos, direction, raycast_params)
	if not raycast_result then create_laser(muzzle_pos, target_pos) return false end
	
	create_laser(muzzle_pos, raycast_result.Position)
	local limb = raycast_result.Instance
	
	local target_character, target_humanoid = find_character(limb.Parent)
	if not target_character or not target_humanoid or target_humanoid.Health <= 0 or has_same_team(target_character, player) 
	or target_character:FindFirstChildOfClass("ForceField") then return false end
	
	tag_humanoid(target_humanoid, player)
	target_humanoid:TakeDamage(damage)
	
	return true
end