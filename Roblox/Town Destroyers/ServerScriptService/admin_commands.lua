
local Players = game:GetService("Players")
local ServerStorage = game:GetService("ServerStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")

local gear_essentials = require(ReplicatedStorage.Modules.GearEssentials)

local display = ReplicatedStorage.DisplayMessage
local gears = ServerStorage.Gears:GetChildren()

local commands : {[string]: any}
commands = {
	["/cmds"] = function(player : Player)
		local text = ""
		for key : string, value in pairs(commands) do
			if key ~= "/cmds" then
				text ..= key .. "\n"
			end
		end
		display:FireClient(player, text, Color3.new(0.8, 0.3, 0.4), 0, 0, true)
	end,
	["/gear "] = function(player : Player, tool : string)
		local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
		if not gear_essentials.character_alive(humanoid) then return end
		
		local backpack = player:FindFirstChild("Backpack")
		local new_gear
			
		if tool:lower() == "all" then
			for _, gear in pairs(gears) do
				new_gear = gear:Clone()
				new_gear.Parent = backpack
			end
			return
		end
		
		for _, gear in pairs(gears) do
			if gear.Name:lower() == tool:lower() then
				new_gear = gear:Clone()
				new_gear.Parent = backpack
				return
			end
		end
	end,
	["/money "] = function(player : Player, money : number)
		if tonumber(money) then
			local leaderstats = player:FindFirstChild("leaderstats") :: Folder
			if not leaderstats then return end
			
			local cash = leaderstats:FindFirstChild("Cash") :: IntValue
			if not cash then return end
			
			cash.Value = money
		end
	end,
	["/speed "] = function(player, value)
		local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
		if not gear_essentials.character_alive(humanoid) then return end
		
		if tonumber(value) then
			humanoid.WalkSpeed = value
		elseif value:lower() == "normal" or value:lower() == "default" then
			humanoid.WalkSpeed = 16
		end
	end,
	["/kick "] = function(player : Player, person : string)
		local players = Players:GetChildren()
		
		if person:lower() == "all" then
			for _, player in pairs(players) do
				player:Kick()
			end	
			return
		end
		
		if person:lower() == "me" then
			person = player.Name
		end
		
		for _, player in pairs(players) do
			if player.Name:lower() == person:lower() then
				player:Kick()
				return
			end
		end
	end, 
	["/kill "] = function(player : Player, person : string)
		local models = workspace:GetChildren()
		
		if person:lower() == "all" then
			for _, character in pairs(models) do
				local humanoid = character:FindFirstChild("Humanoid")
				if gear_essentials.character_alive(humanoid) then
					humanoid.Health = 0
				end
			end	
		else
			if person:lower() == "me" then
				person = player.Name
			end
			for _, character in pairs(models) do
				if character.Name:lower() == person:lower() then
					local humanoid = character:FindFirstChild("Humanoid")
					if gear_essentials.character_alive(humanoid) then
						humanoid.Health = 0
					end
					return
				end
			end
		end
	end,
	["/god"] = function(player)
		local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
		if not gear_essentials.character_alive(humanoid) or character:FindFirstChild("GodForceField") then return end
		
		local forcefield = Instance.new("ForceField")
		forcefield.Name = "GodForceField"
		forcefield.Visible = false
		forcefield.Parent = character
	end,
	["/ungod"] = function(player)
		local character, humanoid = table.unpack(gear_essentials.get_character_from_player(player))
		if not gear_essentials.character_alive(humanoid) then return end
		
		local forcefield = character:FindFirstChild("GodForceField")
		if forcefield then
			forcefield:Destroy()
		end
	end,
	["/tp "] = function(player, arguments)
		local models = workspace:GetChildren()
		
		local people = arguments:split(" ")
		if people[1]:lower() == "me" then
			people[1] = player.Name	
		end
		if people[2]:lower() == "me" then
			people[2] = player.Name
		end
		
		local player1, player2
		for _, character in pairs(models) do
			if character.Name:lower() == people[1]:lower() then
				player1 = character
			elseif character.Name:lower() == people[2]:lower() then
				player2 = character
			end
		end
		
		if not gear_essentials.character_alive(player2) then return end
		
		if people[1]:lower() == "all" then
			for _, character in pairs(models) do
				if gear_essentials.character_alive(character) then
					character:MoveTo(player2:FindFirstChild("Head").Position)	
				end
			end
			return
		end
		
		if gear_essentials.character_alive(player1) then
			player1:MoveTo(player2.Head.Position)
		end
	end,
}

Players.PlayerAdded:Connect(function(player)
	if table.find(_G.admins, player.UserId) then
		player.Chatted:Connect(function(message : string)
			task.wait()
			for command : string, action in pairs(commands) do
				if message:sub(1, command:len()):lower() == command then
					local value = message:sub(command:len() + 1)
					commands[command](player, value)
					break
				end
			end
		end)
	end
end)
