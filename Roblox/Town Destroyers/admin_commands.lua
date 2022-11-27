
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local ServerStorage = game:GetService("ServerStorage")
local Players = game:GetService("Players")

local display = game.ReplicatedStorage.DisplayMessage
local gears = ServerStorage:GetChildren()

local commands 
commands = {
	["/cmds"] = function(player)
		local text = ""
		for key,value in pairs(commands) do
			if key ~= "/cmds" then
				text ..= key .. "\n"
			end
		end
		display:FireClient(player, text, Color3.new(0.8, 0.3, 0.4), 0, 0, true)
	end,
	["/gear "] = function(player, tool)
		local character = workspace:FindFirstChild(player.Name)
		if character then
			local humanoid = character:FindFirstChild("Humanoid")
			if humanoid and humanoid.Health ~= 0 then
				local new_gear
				
				if tool:lower() == "all" then
					for _, gear in pairs(gears) do
						new_gear = gear:Clone()
						new_gear.Parent = player.Backpack
					end
				else
					for _, gear in pairs(gears) do
						if gear.Name:lower() == tool:lower() then
							new_gear = gear:Clone()
							new_gear.Parent = player.Backpack	
							return
						end
					end
				end
			end
		end
	end,
	["/money "] = function(player, money)
		if tonumber(money) then
			player.leaderstats.Cash.Value += money
		end
	end,
	["/speed "] = function(player, value)
		local character = workspace:FindFirstChild(player.Name)
		if character then
			local humanoid = character:FindFirstChild("Humanoid")
			if humanoid and humanoid.Health ~= 0 then
				if tonumber(value) then
					humanoid.WalkSpeed = value
				elseif 
					value:lower() == "normal" or value:lower() == "default" then
					humanoid.WalkSpeed = 16
				end
			end
		end
	end,
	["/kick "] = function(player, person)
		local players = Players:GetChildren()
		
		if person:lower() == "all" then
			for _, player in pairs(players) do
				player:Kick()
			end	
		else
			if person:lower() == "me" then
				person = player.Name
			end
			for _, player in pairs(players) do
				if player.Name:lower() == person:lower() then
					player:Kick()
					return
				end
			end
		end
	end, 
	["/kill "] = function(player, person)
		local models = workspace:GetChildren()
		
		if person:lower() == "all" then
			for _, character in pairs(models) do
				local humanoid = character:FindFirstChild("Humanoid")
				if humanoid and humanoid.Health ~= 0 then
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
					if humanoid and humanoid.Health ~= 0 then
						humanoid.Health = 0
					end
					return
				end
			end
		end
	end,
	["/god"] = function(player)
		local character = workspace:FindFirstChild(player.Name)
		if character then
			local humanoid = character:FindFirstChild("Humanoid")
			if humanoid and humanoid.Health ~= 0 then
				if not character:FindFirstChild("GodForceField") then
					local forcefield = Instance.new("ForceField")
					forcefield.Name = "GodForceField"
					forcefield.Visible = false
					forcefield.Parent = character
				end
			end
		end
	end,
	["/ungod"] = function(player)
		local character = workspace:FindFirstChild(player.Name)
		if character then
			local humanoid = character:FindFirstChild("Humanoid")
			if humanoid and humanoid.Health ~= 0 then
				local forcefield = character:FindFirstChild("GodForceField")
				if forcefield then
					forcefield:Destroy()
				end
			end
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
		
		if people[1]:lower() == "all" then
			if player2 and player2:FindFirstChild("Humanoid") then
				if player2.Humanoid.Health ~= 0 then
					for _, character in pairs(models) do
						if character and character:FindFirstChild("Humanoid") then
							if character.Humanoid.Health ~= 0 then
								character:MoveTo(player2.Head.Position)
							end	
						end
					end
				end
			end
		else
			if player1 and player2 then
				if player1:FindFirstChild("Humanoid") and player2:FindFirstChild("Humanoid") then
					if player1.Humanoid.Health ~= 0 and player2.Humanoid.Health ~= 0 then
						player1:MoveTo(player2.Head.Position)
					end
				end
			end
		end
	end,
}

Players.PlayerAdded:Connect(function(player)
	if table.find(_G.admins, player.UserId) then
		player.Chatted:Connect(function(message)
			task.wait()
			for command, action in pairs(commands) do
				if message:sub(1, command:len()):lower() == command then
					local value = message:sub(command:len() + 1)
					commands[command](player, value)
					break
				end
			end
		end)
	end
end)
