
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local fire_event = ReplicatedStorage.RemoteEvents.FireBullet

local gun_stats = require(ReplicatedStorage.ModuleScripts.GunStats)

local raycast_params = RaycastParams.new()
raycast_params.FilterType = Enum.RaycastFilterType.Blacklist

local round = math.round

function find_character(parent)
	if not parent or parent == workspace then return nil end

	local humanoid : Humanoid = parent:FindFirstChild("Humanoid")
	if not humanoid then return find_character(parent.Parent) end

	return parent, humanoid
end

fire_event.OnServerEvent:Connect(function(player, target_pos, gun_name, muzzle)
	muzzle.MuzzleFlash:Emit(25)
	muzzle.Smoke:Emit(5)
	
	local range = gun_stats[gun_name].range
	local muzzle_pos = muzzle.Position
	local distance = target_pos - muzzle_pos
	local direction = distance.Unit * range
	
	raycast_params.FilterDescendantsInstances = {player.Character}
	local raycast_result = workspace:Raycast(muzzle_pos, direction, raycast_params)
	
	if not raycast_result then return end
	local part = raycast_result.Instance
	
	local character, humanoid : Humanoid = find_character(part.Parent)
	if not character or character:FindFirstChildOfClass("ForceField") 
	or not humanoid or humanoid.Health <= 0 then return end
	
	local damage = round(gun_stats[gun_name].damage * gun_stats[gun_name].damage_dropoff ^ (distance.Magnitude / range))
	humanoid.Health -= damage
end)