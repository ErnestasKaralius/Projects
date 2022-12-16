
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)
local explosive_stats = require(ReplicatedStorage.Modules.ExplosiveStatistics)

local get_mouse_pos = ReplicatedStorage.GetMousePos
local fire_event = ServerStorage.Events.FireEvent

local simple_launcher_rocket = ReplicatedStorage.Shared.SimpleLauncherRocket

local tool = script.Parent
local handle = tool.Handle

local rocket_stats = explosive_stats.basic_launcher

local launch_sound = rocket_stats.launch_sound:Clone()
local reload_sound = rocket_stats.reload_sound:Clone()
launch_sound.Parent = handle
reload_sound.Parent = handle

local cooldown_time = rocket_stats.cooldown_time
local rocket_speed = rocket_stats.rocket_speed

local animation_folder
local launch_animation, reload_animation

local character, humanoid, animator, player

function reload_rocket()
	if gear_essentials.tool_equipped(tool) then
		reload_sound:Play()
		reload_animation:Play()

		local new_rocket = simple_launcher_rocket:Clone()
		new_rocket.Anchored = false
		new_rocket:FindFirstChild("Attachment"):Destroy()

		local left_arm = character:FindFirstChild("Left Arm") or character:FindFirstChild("LeftHand")
		if left_arm then
			new_rocket.CFrame = left_arm:FindFirstChild("LeftGripAttachment").WorldCFrame * CFrame.new(0, 0, -0.5)

			local weld = Instance.new("WeldConstraint")
			weld.Part0 = left_arm
			weld.Part1 = new_rocket
			weld.Parent = new_rocket
			Debris:AddItem(new_rocket, 0.75)
			new_rocket.Parent = character
		end
	end
end

tool.Activated:Connect(function()
	if not tool.Enabled or not gear_essentials.character_alive(humanoid) then return end
	
	local target_pos = get_mouse_pos:InvokeClient(player)
	local spawn_pos = handle.Position + (handle.CFrame.upVector * (handle.Size.Y / 2))
	
	local rocket = simple_launcher_rocket:Clone()
	rocket.CFrame = CFrame.lookAt(spawn_pos, target_pos) * CFrame.Angles(math.pi / 2, 0, 0)
	rocket.Parent = workspace
	
	launch_sound:Play()
	launch_animation:Play()
	
	fire_event:Fire(player, rocket, -rocket.CFrame.UpVector * rocket_speed, rocket_stats)
	
	tool.Enabled = false
	handle.Mesh.MeshId = "rbxassetid://31611841"
	
	task.wait(cooldown_time)
	
	reload_rocket()
	task.wait(0.75)
	
	tool.Enabled = true
	handle.Mesh.MeshId = "rbxassetid://31601544"
end)

tool.Equipped:Connect(function()
	character, humanoid, player = table.unpack(gear_essentials.get_player_components(tool))
	animator = humanoid:FindFirstChild("Animator")
	
	animation_folder = (humanoid.RigType == Enum.HumanoidRigType.R15) and rocket_stats.animation_folder.R15 or rocket_stats.animation_folder.R6
	launch_animation = animator:LoadAnimation(animation_folder.Kickback)
	reload_animation = animator:LoadAnimation(animation_folder.Reload)
end)

tool.Unequipped:Connect(function()
	if launch_animation then launch_animation:Stop() end
	if reload_animation then reload_animation:Stop() end
end)