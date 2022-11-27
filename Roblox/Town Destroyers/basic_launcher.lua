
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")
local Debris = game:GetService("Debris")
local RunService = game:GetService("RunService")

local gear_essentials = require(ReplicatedStorage.GearEssentials)

local explode_event = ServerStorage.Events.ExplodeEvent
local fire_event = ServerStorage.Events.FireEvent
local get_mouse_pos = ReplicatedStorage.GetMousePos

local simple_launcher_rocket = ServerStorage.Shared.SimpleLauncherRocket

local tool = script.Parent
local handle = tool.Handle

local launch_sound = handle.Launch
local reload_sound = handle.Reload
local explode_sound = ServerStorage.Shared.BasicLauncherExplodeSound

local cooldown_time = 10
local rocket_speed = 30
local lifetime = 30

local animation_folder
local launch_animation, reload_animation

local character, humanoid, animator, player

function reload_rocket()
	if tool and tool.Parent and tool.Parent:FindFirstChild("Humanoid") then
		reload_sound:Play()
		reload_animation:Play()

		local new_rocket = simple_launcher_rocket:Clone()
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
	Debris:AddItem(rocket, lifetime)
	rocket.Parent = workspace
	
	local touched_event
	touched_event = rocket.Touched:Connect(function(part)
		if not part or not part.Parent or part:IsDescendantOf(character) then return end
		
		explode_event:Fire(player, rocket, 10, 10000, 0, explode_sound)
		rocket.Attachment:FindFirstChild("Fire").Enabled = false
		rocket.Attachment:FindFirstChild("Smoke").Enabled = false
		touched_event:Disconnect()
	end)
	
	launch_sound:Play()
	launch_animation:Play()
	
	fire_event:Fire(rocket, -rocket.CFrame.UpVector * rocket_speed, lifetime)
	
	tool.Enabled = false
	handle.Mesh.MeshId = "rbxassetid://31611841"
	
	task.wait(cooldown_time)
	
	reload_rocket()
	task.wait(0.75)
	
	tool.Enabled = true
	handle.Mesh.MeshId = "rbxassetid://31601544"
end)

tool.Equipped:Connect(function()
	character = tool.Parent
	humanoid = character:FindFirstChild("Humanoid")
	animator = humanoid:FindFirstChild("Animator")
	player = Players:GetPlayerFromCharacter(character)
	
	animation_folder = (humanoid.RigType == Enum.HumanoidRigType.R15) and tool.Animations.R15 or tool.Animations.R6
	launch_animation = animator:LoadAnimation(animation_folder.Kickback)
	reload_animation = animator:LoadAnimation(animation_folder.Reload)
end)

tool.Unequipped:Connect(function()
	if launch_animation then launch_animation:Stop() end
	if reload_animation then reload_animation:Stop() end
end)