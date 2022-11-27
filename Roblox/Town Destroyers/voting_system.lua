
local Players = game:GetService("Players")
local ReplicatedStorage = game:GetService("ReplicatedStorage")

local display = ReplicatedStorage.DisplayMessage
local map = workspace.Buildings:Clone()
local reseting = false

local casted, required 
_G.voted = { }

local ceil = math.ceil

function reset_map()
	local new_map = map:Clone()
	reseting = true

	task.wait(2)
	workspace.Buildings:Destroy()
	task.wait(1)
	new_map.Parent = workspace

	_G.voted = { }
	reseting = false

	display:FireAllClients("map_reset_success", Color3.new(0, 0.3, 0.6))
end

Players.PlayerAdded:Connect(function(player)
	required = ceil((#Players:GetPlayers()) * 0.6)
	
	player.Chatted:Connect(function(message)
		task.wait()
		if message:lower() == "/vote" then
			if reseting == false then
				if not table.find(_G.voted, player) then
					table.insert(_G.voted, player)
					
					casted = #_G.voted
				
					if casted == 1 then
						display:FireAllClients("progress_voting_single_vote",Color3.new(0, 0.6, 0), 1, required)
					else
						display:FireAllClients("progress_voting",Color3.new(0, 0.6, 0), casted, required)
					end
					
					if casted >= required then
						display:FireAllClients("reset_notification", Color3.new(0, 0.3, 0.6))
						reset_map()
					end
				else
					display:FireClient(player, "already_voted", Color3.new(0.6, 0.05, 0.2))
				end
			else
				display:FireClient(player, "cannot_vote", Color3.new(0.6, 0.05, 0.2))
			end
		elseif message:lower() == "/reset" and table.find(_G.admins, player.UserId) then
			if reseting == false then
				display:FireAllClients("admin_reset_notification", Color3.new(0, 0.3, 0.6))
				reset_map()
			end
		end
	end)
	
	while true do
		if not table.find(_G.voted, player) then
			display:FireClient(player, "vote_reminder", Color3.new(0.55, 0.45, 0))
			task.wait(600) -- 10 minutes
		end
	end
end)

Players.PlayerRemoving:Connect(function(player)
	if reseting == false then
		table.remove(_G.voted, table.find(_G.voted, player))
		
		casted = #_G.voted
		required = ceil((#Players:GetPlayers()) * 0.6)
		
		if casted >= required then
			display:FireAllClients("reset_notification", Color3.new(0, 0.3, 0.6))
			reset_map()
		end
	end
end)

