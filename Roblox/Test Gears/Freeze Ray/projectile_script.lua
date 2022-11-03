
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local pellet = script.Parent

local hit_sound = pellet.HitSound
local creator = pellet.Creator.Value

local shards = 5
local random = math.random

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

function has_same_team(character)
	local target_player = Players:GetPlayerFromCharacter(character)
	if not target_player then return false end
	
	local target_team = target_player.Team
	local creator_team = creator.Team
	
	if not target_team or not creator_team or target_team ~= creator_team then return false end
	return true
end

local touch_event
touch_event = pellet.Touched:Connect(function(limb)
	if limb.Name == "Projectile" then return end
	
	local character, humanoid = find_character(limb.Parent)
	if character and character.Name == creator.Name then return end
	if humanoid and humanoid.Health ~= 0 and not character:FindFirstChildOfClass("ForceField") and not has_same_team(character) then 
		local torso = character:FindFirstChild("Torso") or character:FindFirstChild("UpperTorso")
		
		hit_sound.Parent = torso
		hit_sound:Play()
		
		local ice_cube = Instance.new("Part")
		ice_cube.Name = "Ice Cube"
		ice_cube.Velocity = pellet.Velocity
		ice_cube.Position = torso.Position
		ice_cube.Size = Vector3.new(torso.Size.X + 4, torso.Size.Y + 4, torso.Size.Z + 4)
		ice_cube.Color = Color3.fromRGB(175, 221, 255)
		ice_cube.Material = Enum.Material.Plastic
		ice_cube.Transparency = 0.35
		ice_cube.Reflectance = 0.5
		ice_cube.Shape = 1
		ice_cube.Locked = true
		ice_cube.CanCollide = true
		ice_cube.Anchored = true
		ice_cube.Parent = workspace
		
		local smoke = Instance.new("Smoke")
		smoke.Parent = ice_cube

		local weld = Instance.new("Weld")
		weld.Part0 = ice_cube
		weld.Part1 = torso
		weld.Parent = ice_cube

		Debris:AddItem(ice_cube, 3)
	end
	
	for i=1, shards do
		local part = Instance.new("Part")
		part.Color = Color3.fromRGB(175, 221, 255)
		part.Size = Vector3.new(1, 0.4, 1)
		part.Material = Enum.Material.Ice

		part.Velocity = pellet.Velocity * (4 + random() * 2)
		part.RotVelocity = Vector3.new(random(-20, 20), random(-20, 20), random(-20, 20))
		part.Position = pellet.Position + pellet.Velocity * random() * 0.05 + Vector3.new(0, random() * 3, 0)
		part.Parent = workspace

		Debris:AddItem(part, 30)
	end
	touch_event:Disconnect()
	pellet:Destroy()
end)

Debris:AddItem(pellet, 5)