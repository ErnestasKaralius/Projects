
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local experience_changed = ReplicatedStorage.Remotes.ExperienceChanged
local request_data = ReplicatedStorage.Remotes.RequestData

local level_text = script.Parent.Level
local xp_bar = script.Parent.Container.Fill

local formulas = require(ReplicatedStorage.Modules.Formulas)
local languages = require(ReplicatedStorage.Modules.Languages)

local latest_xp, latest_required, latest_level
local is_looping = false

local tween_time = 0.75

experience_changed.OnClientEvent:Connect(function(old_level, new_level, experience)
	
	latest_xp = experience - formulas.experience_sum(new_level)
	latest_required = formulas.required_experience(new_level + 1)
	latest_level = new_level
	
	if not is_looping then -- to ensure that we only have ONE loop at a time
		while old_level < latest_level do
			is_looping = true
			xp_bar:TweenSize(UDim2.new(1, 5, 1, 0), Enum.EasingDirection.Out, Enum.EasingStyle.Linear, tween_time, true)
			
			task.wait(tween_time)
			xp_bar.Size = UDim2.new(0, 5, 1, 0)
			old_level += 1
			level_text.Text = languages[_G.language].level_indicator(old_level)
		end
		is_looping = false
	end
	
	if not is_looping then -- to not break up the loop
		xp_bar:TweenSize(UDim2.new(latest_xp / latest_required, 5, 1, 0), Enum.EasingDirection.Out, Enum.EasingStyle.Linear, tween_time, true)
	end
end)

do
	local data = request_data:InvokeServer()

	local remaining_xp = data.xp - formulas.experience_sum(data.level)
	local required_for_next_level = formulas.required_experience(data.level + 1)

	level_text.Text = languages[_G.language].level_indicator(data.level)
	xp_bar.Size = UDim2.new(remaining_xp / required_for_next_level, 5, 1, 0)
end





