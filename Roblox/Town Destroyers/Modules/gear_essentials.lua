--!strict
---------------------------------
-- Made by karalius2121 (Kara) --
---------------------------------

local Players = game:GetService("Players")
local ContextActionService = game:GetService("ContextActionService")
local Debris = game:GetService("Debris")

local gear_essentials = {}

function gear_essentials.find_character(parent : Instance?): {[number] : Model | Humanoid}
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
	for _, tag : ObjectValue in pairs(target_humanoid:GetChildren() :: {}) do
		if tag and tag.Parent and tag.Name == "creator" then tag:Destroy() end
	end

	local creator_tag = Instance.new("ObjectValue")
	creator_tag.Name = "creator"
	creator_tag.Value = attacking_player
	Debris:AddItem(creator_tag, 1)
	creator_tag.Parent = target_humanoid
end

function gear_essentials.has_same_team(target_character : Model, attacking_player : Player) : boolean
	local target_player : Player = Players:GetPlayerFromCharacter(target_character)
	if not target_player then return false end

	local target_team : Team? = target_player.Team
	local creator_team : Team? = attacking_player.Team

	if not target_team or not creator_team or target_team ~= creator_team then return false end

	return true
end

function gear_essentials.character_alive(humanoid : Humanoid) : boolean
	if not humanoid or not humanoid.Parent or humanoid.Health <= 0 then return false end
	return true
end

function gear_essentials.raycast_to_character(origin: Vector3, target : Vector3, range : Vector3, original_character : Model) : {[number] : Model | Humanoid}
	local raycast_params = RaycastParams.new()
	raycast_params.FilterType = Enum.RaycastFilterType.Blacklist
	raycast_params.FilterDescendantsInstances = {original_character}
	
	local direction : Vector3 = (target - origin).Unit * range
	
	local raycast_result = workspace:Raycast(origin, direction, raycast_params)
	if not raycast_result then return {} end
	
	local limb : Part = raycast_result.Instance
	local character, humanoid = table.unpack(gear_essentials.find_character(limb.Parent))
	
	return {character, humanoid}
end

function gear_essentials.get_object_mass(object : Instance) : number
	local mass : number = object:IsA("BasePart") and object:GetMass() or 0

	for _, part : Part in pairs(object:GetDescendants() :: {}) do
		if part:IsA("BasePart") then
			mass += part:GetMass()
		end
	end

	return mass
end

function gear_essentials.tool_equipped(tool : Tool) : boolean
	if tool and tool.Parent and tool.Parent:FindFirstChild("Humanoid") then return true end
	return false
end

function gear_essentials.get_player_components(tool: Tool) : {[number] : Model | Humanoid | Player}
	local character : Instance? = tool.Parent
	if not character then return {} end
	
	return {character :: Model, (character :: Model):FindFirstChild("Humanoid") :: Humanoid, Players:GetPlayerFromCharacter(character)}
end

function gear_essentials.get_character_from_player(player : Player) : {[number] : Model | Humanoid}
	local character : Model? = player.Character
	if not character then return {} end
	
	return {character :: Model, (character :: Model):FindFirstChild("Humanoid") :: Humanoid}
end

function gear_essentials.unbind_actions(... : string)
	for _, action : string in pairs(table.pack(...) :: {}) do
		ContextActionService:UnbindAction(action)
	end
end

return gear_essentials
