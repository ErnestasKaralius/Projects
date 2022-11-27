
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local RunService = game:GetService("RunService")

local gear_essentials = require(ReplicatedStorage.GearEssentials)
local get_mouse_target = ReplicatedStorage.GetMouseTarget

local magnet = script.Parent
local handle = magnet.Handle
local electricity_particles = handle.ParticleAttachment.Electricity

local max_distance = 50
local min_distance = 0.5
local speed = 10

local attracting = false

local character, humanoid, humanoid_root, player
local linear_velocity, attachment

magnet.Activated:Connect(function()
	if not gear_essentials.character_alive(humanoid) then return end
	
	local part = get_mouse_target:InvokeClient(player)
	if not part or (part.Position - humanoid_root.Position).Magnitude > max_distance then return end
	
	local target_character, target_humanoid = table.unpack(gear_essentials.find_character(part.Parent))
	if target_character and target_humanoid.Health ~= 0 then
		local root_part = target_character:FindFirstChild("HumanoidRootPart")
		if not root_part then return end

		part = root_part
		
	elseif part.Anchored then 
		return 
	end

	attracting = true
	electricity_particles.Enabled = true
	
	while attracting and part and part.Parent and gear_essentials.character_alive(humanoid) 
	and magnet.Parent and magnet.Parent:FindFirstChild("Humanoid") do
		local one_frame = RunService.Heartbeat:Wait()
		local distance = (part.Position - humanoid_root.Position).Magnitude
		if distance > min_distance and distance < max_distance then
			local direction = CFrame.lookAt(humanoid_root.Position, part.Position).LookVector
			part.Position -= direction * one_frame * speed
		end
	end
	
	electricity_particles.Enabled = false
	attracting = false
end)

magnet.Deactivated:Connect(function()
	attracting = false
end)

magnet.Equipped:Connect(function()
	character = magnet.Parent
	humanoid = character:FindFirstChild("Humanoid")
	humanoid_root = character:FindFirstChild("HumanoidRootPart")
	
	player = Players:GetPlayerFromCharacter(character)
end)

