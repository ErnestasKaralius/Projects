--!strict
---------------------------------
-- Made by karalius2121 (Kara) --
---------------------------------

local Players = game:GetService("Players")
local ContextActionService = game:GetService("ContextActionService")
local Debris = game:GetService("Debris")

local gear_essentials = {}

function gear_essentials.find_character(parent : Instance?): {Model | Humanoid}
	if parent and parent ~= workspace then
		local humanoid = parent:FindFirstChild("Humanoid") :: Humanoid
		if humanoid then
			return {parent :: Model, humanoid}
		else
			return gear_essentials.find_character(parent.Parent)
		end
	end
	return {}
end

function gear_essentials.tag_humanoid(target_humanoid : Humanoid, attacking_player : Player)
	for _, tag  in pairs(target_humanoid:GetChildren()) do
		if tag and tag.Parent and tag.Name == "creator" then tag:Destroy() end
	end

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Name = "creator"
	creator_tag.Value = attacking_player
	Debris:AddItem(creator_tag, 1)
	creator_tag.Parent = target_humanoid
end

function gear_essentials.has_same_team(target_player : Player | Model, attacking_player : Player | Model) : boolean
	if target_player:FindFirstChild("Humanoid") then
		target_player = Players:GetPlayerFromCharacter(target_player)
	end
	
	if attacking_player:FindFirstChild("Humanoid") then
		attacking_player = Players:GetPlayerFromCharacter(attacking_player)
	end
	
	if not target_player or not attacking_player then return false end

	return (target_player :: Player).Team == (attacking_player :: Player).Team
end

function gear_essentials.character_alive(character)
	if not character then return false end
	
    local humanoid = (character:FindFirstChildWhichIsA("Humanoid") or character) :: Humanoid
    return humanoid and humanoid.Health > 0
end

function gear_essentials.raycast_to_character(origin: Vector3, target : Vector3, range : Vector3, original_character : Model) : {[number] : Model | Humanoid}
	local raycast_params = RaycastParams.new()
	raycast_params.FilterType = Enum.RaycastFilterType.Blacklist
	raycast_params.FilterDescendantsInstances = {original_character}
	
	local direction : Vector3 = (target - origin).Unit * range
	
	local raycast_result = workspace:Raycast(origin, direction, raycast_params)
	if not raycast_result then return {} end
	
	local limb = raycast_result.Instance
	local character, humanoid = table.unpack(gear_essentials.find_character(limb.Parent))
	
	return {character, humanoid}
end

function gear_essentials.get_object_mass(object : Instance) : number
	local mass : number = object:IsA("BasePart") and object:GetMass() or 0

	for _, part in pairs(object:GetDescendants()) do
		if part:IsA("BasePart") then
			mass += part:GetMass()
		end
	end

	return mass
end

function gear_essentials.tool_equipped(tool : Tool)
	return (tool and tool.Parent and tool.Parent:FindFirstChild("Humanoid") ~= nil) :: boolean
end

function gear_essentials.get_player_components(tool: Tool) : {Model | Humanoid | Player}
	local character = tool.Parent :: Model
	if not character then return {} end
	
	local humanoid = character:FindFirstChild("Humanoid") :: Humanoid
	if not humanoid then return {} end
	
	local player = Players:GetPlayerFromCharacter(character)
	if not player then return {} end
	
	return {character, humanoid, player}
end

function gear_essentials.get_character_from_player(player : Player) : {Model | Humanoid}
	local character = player.Character :: Model
	if not character then return {} end
	
	local humanoid = character:FindFirstChild("Humanoid") :: Humanoid
	if not humanoid then return {} end
	
	return {character, humanoid}
end

function gear_essentials.unbind_actions(... : string)
	for _, action in pairs(table.pack(...)) do
		ContextActionService:UnbindAction(action)
	end
end

return gear_essentials
