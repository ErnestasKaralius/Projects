
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")

local gear_essentials = require(ReplicatedStorage.GearEssentials)

local pistol = script.Parent
local handle = pistol.Handle
local slide = pistol.Bolt

local muzzle = slide.ParticleAttachment
local muzzle_flash = muzzle.MuzzleFlash
local smoke = muzzle.Smoke

local get_mouse_pos = ReplicatedStorage.GetMousePos
local reload_event = pistol.UserInputHandler.Reload

local fire_sound = handle.PistolFire
local empty_sound = handle.PistolEmpty
local reload_sound = handle.PistolReload

local ammo = script.Ammo
local clip_size = script.ClipSize

local max_ammo = pistol:GetAttribute("MaxAmmo")
local max_clip_size = pistol:GetAttribute("MaxClipSize")

ammo.Value = max_ammo
clip_size.Value = max_clip_size

local damage = 25
local damage_dropoff = 0.8
local range = 200

local reloading = false

local character, humanoid : Humanoid, player

reload_event.OnServerEvent:Connect(function()
	if reloading or ammo.Value <= 0 or clip_size.Value > max_clip_size then return end

	reload_sound:Play()
	reloading = true
	
	local end_time = time() + reload_sound.TimeLength
	while task.wait() and time() < end_time do
		if not pistol.Parent or not pistol.Parent:FindFirstChild("Humanoid") then
			reload_sound:Stop()
			reloading = false
			return
		end
	end
	
	reloading = false
	
	local needed = max_clip_size - clip_size.Value
	if clip_size.Value == max_clip_size then
		clip_size.Value += 1
		ammo.Value -= 1
	elseif ammo.Value > needed then
		clip_size.Value = max_clip_size
		ammo.Value -= needed
	else
		clip_size.Value += ammo.Value
		ammo.Value = 0
	end
	
end)

pistol.Activated:Connect(function()
	if reloading or not gear_essentials.character_alive(humanoid) then return end
	
	if clip_size.Value <= 0 then
		empty_sound:Play()
		return
	end
	
	fire_sound:Play()
	clip_size.Value -= 1
	
	muzzle_flash:Emit(25)
	muzzle_flash:Emit(5)
	
	local mouse_pos = get_mouse_pos:InvokeClient(player)

	local target_character, target_humanoid = table.unpack(gear_essentials.raycast_to_character(muzzle.WorldPosition, mouse_pos, range, character))
	if not target_character or gear_essentials.has_same_team(target_character, player) or target_humanoid.Health <= 0 then return end
	
	gear_essentials.tag_humanoid(target_humanoid, player)
	target_humanoid:TakeDamage(math.round(damage * damage_dropoff ^ ((mouse_pos - muzzle.WorldPosition).Magnitude / range)))
end)

pistol.Equipped:Connect(function()
	character = pistol.Parent
	humanoid = character:FindFirstChild("Humanoid")
	player = Players:GetPlayerFromCharacter(character)
end)
