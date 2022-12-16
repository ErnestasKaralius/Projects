
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local explosive_stats = require(ReplicatedStorage.Modules.ExplosiveStatistics)

local get_mouse_pos = ReplicatedStorage.GetMousePos
local fire_event = ServerStorage.Events.FireEvent

local tool = script.Parent
local handle = tool.Handle

local super_launcher_rocket = ReplicatedStorage.Shared:FindFirstChild("SuperLauncherRocket")

local launch_sound = explosive_stats.super_launcher.launch_sound:Clone()
local reload_sound = explosive_stats.super_launcher.reload_sound:Clone()
launch_sound.Parent = handle 
reload_sound.Parent = handle

local animation_folder
local reload_animation

local rocket_stats = explosive_stats.super_launcher

local cooldown_time = rocket_stats.cooldown_time
local rocket_speed = rocket_stats.rocket_speed
local dive_speed = rocket_stats.dive_speed
local rise_time = rocket_stats.rise_time

local rocket_spread = 6
local rocket_offsets = {
	Vector3.new(0, 0, 0),
	Vector3.new(rocket_spread, 0, 0), Vector3.new(0, 0, rocket_spread),
	Vector3.new(-rocket_spread, 0, 0), Vector3.new(0, 0, -rocket_spread)
}

local character, humanoid, animator, player

function reload_rockets()
	for i = 1, #rocket_offsets do
		if gear_essentials.tool_equipped(tool) then
			reload_sound:Play()
			reload_animation:Play()

			local new_rocket = super_launcher_rocket:Clone()
			new_rocket.Anchored = false
			new_rocket:FindFirstChild("Fire"):Destroy()

			local left_arm = character:FindFirstChild("Left Arm") or character:FindFirstChild("LeftHand")
			if left_arm then
				new_rocket.CFrame = left_arm:FindFirstChild("LeftGripAttachment").WorldCFrame * CFrame.new(0, 0, -0.5)

				local weld = Instance.new("WeldConstraint")
				weld.Part0 = left_arm
				weld.Part1 = new_rocket
				weld.Parent = new_rocket
				Debris:AddItem(new_rocket, reload_animation.Length * 0.7)
				new_rocket.Parent = character
			end
		end
		task.wait(reload_animation.Length)
		reload_sound:Stop()
	end
	tool.Enabled = true	
end

function launch_rocket(target_pos)
	task.spawn(function()
		launch_sound.PlaybackSpeed = math.random(90, 110) / 100
		launch_sound:Play()
		
		local rocket = super_launcher_rocket:Clone()
		rocket.Position = handle.Muzzle.WorldPosition
		rocket.Parent = workspace
		
		fire_event:Fire(player, rocket, rocket.CFrame.LookVector * rocket_speed, explosive_stats.super_launcher)
		
		task.delay(rise_time, function()
			if not rocket or not rocket.Parent or rocket.Transparency == 1 then return end
			rocket.CFrame = CFrame.lookAt(rocket.Position, target_pos)
			fire_event:Fire(player, rocket, rocket.CFrame.LookVector * dive_speed, explosive_stats.super_launcher)
		end)
	end)
end

tool.Activated:Connect(function()
	if not tool.Enabled or not gear_essentials.character_alive(humanoid) then return end
	tool.Enabled = false
	
	local mouse_pos = get_mouse_pos:InvokeClient(player)
	
	for i = 1, #rocket_offsets do
		if gear_essentials.tool_equipped(tool) then 
			launch_rocket(mouse_pos) 
		end
		task.wait(0.2)
	end
	
	task.wait(cooldown_time)
	reload_rockets()
end)

tool.Equipped:Connect(function()
	character, humanoid, player = table.unpack(gear_essentials.get_player_components(tool))
	animator = humanoid:FindFirstChild("Animator")
	
	animation_folder = (humanoid.RigType == Enum.HumanoidRigType.R15) and rocket_stats.animation_folder.R15 or rocket_stats.animation_folder.R6
	reload_animation = animator:LoadAnimation(animation_folder.Reload)
end)

tool.Unequipped:Connect(function()
	if reload_animation then reload_animation:Stop() end
end)