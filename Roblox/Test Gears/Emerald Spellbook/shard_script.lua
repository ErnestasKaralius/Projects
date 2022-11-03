
local Players = game:GetService("Players")
local Debris = game:GetService("Debris")

local emerald = script.Parent
local hit_sound = emerald:FindFirstChild("HitSound")

local creator = emerald.creator.Value

local exploded = false
local can_hit = false
local random = math.random

function tag_humanoid(humanoid)
	for _, tag in pairs(humanoid:GetChildren()) do
		if tag and tag.Parent and tag.Name == "creator" then tag:Destroy() end
	end

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Name = "creator"
	creator_tag.Value = creator
	Debris:AddItem(creator_tag, 1)
	creator_tag.Parent = humanoid
end

function has_same_team(character)
	local target_player = Players:GetPlayerFromCharacter(character)
	if not target_player then return false end

	local target_team = target_player.Team
	local creator_team = creator.Team

	if not target_team or not creator_team or target_team ~= creator_team then return false end
	return true
end

emerald.Touched:Connect(function(limb)
	if not exploded and limb and limb.Name ~= "Effect" and limb.Name ~= "Handle" then
		local character = limb.Parent
		if character and character.Name ~= creator.Name then 
			local humanoid = character:FindFirstChild("Humanoid")
			if humanoid and humanoid.Health ~= 0 and not has_same_team(character) then
				tag_humanoid(humanoid)
				humanoid:TakeDamage(emerald:FindFirstChild("Motor") and 16 or 26)
				can_hit = true
			end
		end
	end
	
	if can_hit or not emerald:FindFirstChild("Motor") then
		exploded=true
		hit_sound:Play()
		
		for i=1, random(4, 8) do
			local wedge = Instance.new("WedgePart")
			wedge.Name="EmeraldShard"
			wedge.Transparency = emerald.Transparency
			wedge.Reflectance = emerald.Reflectance
			wedge.BrickColor = emerald.BrickColor
			wedge.FormFactor = "Custom"
			wedge.Size = Vector3.new(0.5, 0.5, 0.5) + Vector3.new(random(), random(), random())
			wedge.TopSurface = "Smooth"
			wedge.BottomSurface = "Smooth"
			wedge.Anchored = false
			wedge.BrickColor = emerald.BrickColor
			if random() < 0.5 then wedge.CanCollide=false end
		
			local pos = Vector3.new(random() - 0.5, random() - 0.5, random() - 0.5)
			wedge.CFrame = emerald.CFrame * CFrame.new(pos * 4) * CFrame.Angles(random() * 6, random() * 6, random() * 6)
			wedge.Velocity = Vector3.new(0, 30 + (random() * 30), 0) + (pos * random(10, 40))
			wedge.RotVelocity = Vector3.new(random() - 0.5, random() - 0.5, random() - 0.5) * 10
			Debris:AddItem(wedge, 2 + random() * 4)
			wedge.Parent = workspace
		end
		
		emerald.Transparency = 1
		emerald.CanCollide = false
		emerald.Anchored = true
		emerald.Size = Vector3.new(0, 0, 0)
		emerald.CFrame = emerald.CFrame
		
		task.wait(1)
		if emerald then emerald:Destroy() end
	end	
end)

task.wait(20)
script:Destroy()





