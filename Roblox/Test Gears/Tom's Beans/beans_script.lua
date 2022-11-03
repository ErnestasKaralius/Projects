
local tool = script.Parent
local handle = tool.Handle
local mesh = handle.Mesh

local bean_spoon = tool.Spoon
local spoon

local eat_sound = handle.EatSound

local r6_eat_animation = script.R6EatAnimation
local r15_eat_animation = script.R15EatAnimation
local eat_animation

local character, humanoid : Humanoid
local head, face, original_face

local closed_can_texture = "rbxassetid://103920391"
local opened_can_texture = "rbxassetid://103920471"
local eat_face_texture = "rbxassetid://103838612"

local health = 80

function character_alive()
	if character and head and humanoid and humanoid.Health ~= 0 then return true end
	return false
end

tool.Activated:Connect(function()
	if not tool.Enabled or not character_alive() then return end
	tool.Enabled = false
	
	local animator = humanoid:FindFirstChild("Animator")
	if humanoid.RigType == Enum.HumanoidRigType.R15 then
		eat_animation = animator:LoadAnimation(r15_eat_animation)
	else
		eat_animation = animator:LoadAnimation(r6_eat_animation)
	end
	eat_animation:Play()
	
	mesh.TextureId = opened_can_texture
	
	eat_animation.KeyframeReached:Connect(function(key)
		if(key == "eat") then
			eat_sound:Play()
			humanoid.Health += health / 2
		elseif(key == "face") then
			face.Texture = eat_face_texture
		elseif(key == "done") then
			local end_time = time() + 3
			while time() < end_time and task.wait() do
				if not tool.Parent or not tool.Parent:FindFirstChild("Humanoid") then return end
			end
			tool.Enabled = true
			mesh.TextureId = closed_can_texture
			if face then face.Texture = original_face end
		end
	end)
end)

tool.Equipped:Connect(function()
	character = tool.Parent
	head = character:FindFirstChild("Head")
	humanoid = character:FindFirstChild("Humanoid")
	if not character_alive() then return end
	
	face = head:FindFirstChild("face")
	if face then original_face = face.Texture end
	
	local left_arm = character:FindFirstChild("Left Arm") or character:FindFirstChild("LeftHand")
	if not left_arm then return end
	
	spoon = bean_spoon:Clone()
	spoon.Anchored = false
	spoon.Transparency = 0
	spoon.CanTouch = true
	
	if humanoid.RigType == Enum.HumanoidRigType.R15 then
		spoon.CFrame = left_arm.CFrame * CFrame.new(0, 0, -0.5)
	else
		spoon.CFrame = left_arm.LeftGripAttachment.WorldCFrame * CFrame.new(0, 0, -0.5)
	end
	
	local weld = Instance.new("WeldConstraint")
	weld.Part0 = left_arm
	weld.Part1 = spoon
	weld.Parent = spoon
	spoon.Parent = character
end)

tool.Unequipped:Connect(function()
	if spoon then spoon:Destroy() end
	mesh.TextureId = closed_can_texture
	if face then face.Texture = original_face end
	if eat_animation then eat_animation:Stop() end
	tool.Enabled = true
end)
