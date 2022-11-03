
local ContextActionService = game:GetService("ContextActionService")
local RunService = game:GetService("RunService")
local Players = game:GetService("Players")

local player = Players.LocalPlayer
local mouse = player:GetMouse()
local player_gui = player:WaitForChild("PlayerGui")

local character = player.Character 
if not character or not character.Parent then character = player.CharacterAdded:Wait() end
local humanoid : Humanoid = character:WaitForChild("Humanoid")
local animator = humanoid:WaitForChild("Animator")

local tool = script.Parent
local handle = tool:WaitForChild("Handle")
local muzzle = handle:WaitForChild("Muzzle")

local fire_remote_function = script:WaitForChild("Fire")
local reload_sound = handle:WaitForChild("ReloadSound")

local animation_folder = humanoid.RigType == Enum.HumanoidRigType.R15 and script.R15 or script.R6
local hold_animation, reload_animation, shoot_animation

local ammo = math.huge
local clip_size = tool:GetAttribute("ClipSize")
local fire_rate = 0.09
local reload_time = 1.5

local mouse_normal_icon = "rbxassetid://170908665"
local mouse_hit_icon = "rbxassetid://172618259"
local last_hit = 0

local ammo_gui = script:WaitForChild("AmmoDisplay")
local ammo_frame = ammo_gui.Frame:WaitForChild("Ammo")

local ammo_counter = ammo_frame.AmmoCounter:WaitForChild("Counter")
local mag_counter = ammo_frame.MagCounter:WaitForChild("Counter")
mag_counter.Text = clip_size
ammo_counter.Text = (ammo == math.huge) and "-" or ammo

local firing = false
local reloading = false

local transparency_event

function character_alive()
	if not character or not humanoid or humanoid.Health <= 0 then return false end
	return true
end

function reload(action_name, input_state)
	if not character_alive() or input_state ~= Enum.UserInputState.Begin or reloading 
	or clip_size >= tool:GetAttribute("ClipSize") or ammo <= 0 then return end
	
	reloading = true
	
	reload_sound:Play()
	reload_animation = animator:LoadAnimation(animation_folder.ReloadAnimation)
	reload_animation:Play()
	
	local end_time = time() + reload_time
	while time() < end_time and RunService.Heartbeat:Wait() do
		if not tool.Parent or not tool.Parent:FindFirstChild("Humanoid") or not character_alive() then
			reload_animation:Stop()
			reload_sound:Stop()
			reloading = false
			return
		end
	end
	
	reloading = false
	reload_sound:Stop()
	
	local needed = tool:GetAttribute("ClipSize") - clip_size
	if ammo >= needed then
		clip_size += needed
		ammo -= needed
	else
		clip_size += ammo
		ammo = 0
	end

	mag_counter.Text = clip_size
	ammo_counter.Text = (ammo == math.huge) and "-" or ammo
end

function fire(action_name, input_state)
	if input_state == Enum.UserInputState.End then firing = false return end
	if firing then return end
	firing = true
	
	shoot_animation = animator:LoadAnimation(animation_folder.ShootAnimation)
	shoot_animation:Play()
	
	while firing and character_alive() and tool.Parent and tool.Parent:FindFirstChild("Humanoid") and not reloading do
		if fire_remote_function:InvokeServer(mouse.Hit.Position, muzzle.WorldPosition, clip_size) then
			mouse.Icon = mouse_hit_icon
			task.delay(0.8, function()
				if tick() - last_hit < 0.8 then return end
				if mouse.Icon == mouse_hit_icon then mouse.Icon = mouse_normal_icon end
			end)
			last_hit = tick()
		end
		
		if clip_size > 0 then
			clip_size -= 1
			mag_counter.Text = clip_size
		else
			reload("Reload", Enum.UserInputState.Begin)
		end
			
		local end_time = time() + fire_rate
		while time() < end_time and RunService.Heartbeat:Wait() do
			if not firing then shoot_animation:Stop() return end
		end
	end
	firing = false
	shoot_animation:Stop()
end

tool.Equipped:Connect(function()
	if not character_alive() then return end
	
	humanoid.CameraOffset = Vector3.new(0, 0.35, 0)
	ammo_gui.Parent = player_gui
	mouse.Icon = mouse_normal_icon
	
	hold_animation = animator:LoadAnimation(animation_folder.HoldAnimation)
	hold_animation:Play()
	
	ContextActionService:BindAction("Fire", fire, false, Enum.UserInputType.MouseButton1, Enum.UserInputType.Touch, Enum.KeyCode.ButtonR1)
	
	ContextActionService:BindAction("Reload", reload, true, Enum.KeyCode.R, Enum.KeyCode.ButtonY)
	ContextActionService:SetPosition("Reload", UDim2.new(0.25, 0, 0.5, 0))
	ContextActionService:SetImage("Reload", "rbxassetid://7292214461")
	
	local arms = {}
	for _, arm in pairs(character:GetChildren()) do
		local arm_name = arm.Name:lower()
		if arm_name:find("arm") or arm_name:find("hand") then
			table.insert(arms, arm)
		end
	end
	
	transparency_event = RunService.RenderStepped:Connect(function()
		for _, arm in pairs(arms) do
			if not arm or not arm.Parent then table.remove(arms, arm) continue end
			arm.LocalTransparencyModifier = arm.Transparency
		end
	end)
end)

tool.Unequipped:Connect(function()
	if ammo_gui then ammo_gui.Parent = script end
	humanoid.CameraOffset = Vector3.new(0, 0, 0)
	mouse.Icon = ""
	
	hold_animation:Stop()
	transparency_event:Disconnect()
	
	ContextActionService:UnbindAction("Fire")
	ContextActionService:UnbindAction("Reload")
end)