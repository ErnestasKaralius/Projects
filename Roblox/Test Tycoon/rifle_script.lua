
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ContextActionService = game:GetService("ContextActionService")
local RunService = game:GetService("RunService")
local Players = game:GetService("Players")

local player = Players.LocalPlayer
local player_gui = player.PlayerGui
local mouse = player:GetMouse()

local character = player.Character 
if not character or not character.Parent then character = player.CharacterAdded:Wait() end
local humanoid : Humanoid = character:WaitForChild("Humanoid")

local fire_event = ReplicatedStorage.RemoteEvents:WaitForChild("FireBullet")
local gun_stats = require(ReplicatedStorage.ModuleScripts:WaitForChild("GunStats"))

local gun = script.Parent
local gun_name = gun.Name:lower()
local handle = gun.Handle
local muzzle = handle:WaitForChild("ParticleAttachment")

local fire_sound = handle:WaitForChild("FireSound")
local reload_sound = handle:WaitForChild("ReloadSound")

local ammo = gun_stats[gun_name].ammo
local clip_size = gun_stats[gun_name].clip_size
local fire_rate = 1 / gun_stats[gun_name].fire_rate

local ammo_gui = ReplicatedStorage.GunShared:WaitForChild("AmmoGUI"):Clone()
local ammo_text = ammo_gui.Ammunition:WaitForChild("AmmoCount")
ammo_text.Text = clip_size .. "/" .. ammo
ammo_gui.Parent = script

local firing = false
local reloading = false

function character_alive()
	if not character or not humanoid or humanoid.Health <= 0 then return false end
	return true
end

function reload(action_name, input_state)
	if not character_alive() or input_state ~= Enum.UserInputState.Begin or reloading 
	or clip_size >= gun_stats[gun_name].clip_size or ammo <= 0 then return end
	
	reload_sound:Play()
	reloading = true
	
	local end_time = time() + reload_sound.TimeLength
	while time() < end_time and RunService.Heartbeat:Wait() do
		if not gun.Parent or not gun.Parent:FindFirstChild("Humanoid") or not character_alive() then
			reload_sound:Stop()
			reloading = false
			return
		end
	end
	
	reloading = false
	
	local needed = gun_stats[gun_name].clip_size - clip_size
	if ammo >= needed then
		clip_size += needed
		ammo -= needed
	else
		clip_size += ammo
		ammo = 0
	end

	ammo_text.Text = clip_size .. "/" .. ammo
end

function fire(action_name, input_state)
	if input_state == Enum.UserInputState.End then firing = false return end
	if firing then return end
	firing = true

	while firing and character_alive() and gun.Parent and gun.Parent:FindFirstChild("Humanoid") 
		and not reloading and clip_size > 0 do
		fire_event:FireServer(mouse.Hit.Position, gun_name, muzzle)

		clip_size -= 1
		ammo_text.Text = clip_size .. "/" .. ammo

		fire_sound:Play()
		
		local end_time = time() + fire_rate
		while time() < end_time and RunService.Heartbeat:Wait() do
			if not firing then return end
		end
	end
	firing = false
end

gun.Equipped:Connect(function()
	if not character_alive() then return end
	
	ammo_gui.Parent = player_gui
	ammo_text.TextSize = ammo_gui.Ammunition.AbsoluteSize.X * 0.3
	
	ContextActionService:BindAction("Fire", fire, false, Enum.UserInputType.MouseButton1, Enum.UserInputType.Touch, Enum.KeyCode.ButtonR1)
	
	ContextActionService:BindAction("Reload", reload, true, Enum.KeyCode.R, Enum.KeyCode.ButtonY)
	ContextActionService:SetPosition("Reload", UDim2.new(0.25, 0, 0.5, 0))
	ContextActionService:SetImage("Reload", "rbxassetid://7292214461")
end)

gun.Unequipped:Connect(function()
	if ammo_gui then ammo_gui.Parent = script end
	ContextActionService:UnbindAction("Fire")
	ContextActionService:UnbindAction("Reload")
end)