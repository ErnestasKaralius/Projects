
local ReplicatedStorage = game:GetService("ReplicatedStorage")

local shared_folder = ReplicatedStorage.Shared
local anim_folder = shared_folder.Animations
local sounds_folder = shared_folder.Sounds

local statistics = {
	
	scooter = {
		max_speed = 50,
		speed_deceleration = 0.5,
		max_rotation = 5,
		speed_gain = 0.5,
		rotation_gain = 0.125, -- Use 1 / (2^x) pls float points scary :(
		jump_force = 30,
		jump_max_force = 100,
		jump_duration = 0.1,
		jump_interval = 1,
		max_smoke_opacity = 10,
		opacity_inrease_rate = 20,
		wheel_velocity_damper = 250,
		engine_sound = sounds_folder.EngineRoar,
		honk_sound = sounds_folder.Honk,
		animation_folder = anim_folder.Scooter,
		controls = {
			accelerate = { Enum.KeyCode.W, Enum.KeyCode.Up, Enum.KeyCode.ButtonR1 },
			decelerate = { Enum.KeyCode.S, Enum.KeyCode.Down, Enum.KeyCode.ButtonL1 },
			
			steer_left = { Enum.KeyCode.A, Enum.KeyCode.Left },
			steer_right = { Enum.KeyCode.D, Enum.KeyCode.Right },
			
			honk = { Enum.KeyCode.H, Enum.KeyCode.ButtonY }
		}
	},

	basic_launcher = {
		cooldown_time = 10,
		rocket_speed = 30,
		lifetime = 10,
		explode_time = 0,
		blast_radius = 15,
		blast_pressure = 20000,
		explode_sound = sounds_folder.BasicLauncherExplode,
		thrust_sound = sounds_folder.NoSound,
		launch_sound = sounds_folder.Launch,
		reload_sound = sounds_folder.BasicLauncherReload,
		animation_folder = anim_folder.BasicLauncher
	},
	
	super_launcher = {
		cooldown_time = 0.25,
		rocket_speed = 50,
		dive_speed = 90,
		rise_time = 1.5,
		lifetime = 10,
		explode_time = 0,
		blast_radius = 8,
		blast_pressure = 500000,
		explode_sound = sounds_folder.SuperLauncherExplode,
		thrust_sound = sounds_folder.Thrust,
		launch_sound = sounds_folder.Launch,
		reload_sound = sounds_folder.SuperLauncherReload,
		animation_folder = anim_folder.SuperLauncher
	},
	
	exponential_rocket = {
		cooldown_time = 3,
		rocket_speed = 25,
		lifetime = 1.5,
		time_until_split = 0.75,
		explode_time = 0,
		blast_radius = 10,
		blast_pressure = 7000,
		explode_sound = sounds_folder.RocketExplode,
		thrust_sound = sounds_folder.Thrust
	},
	
	bomb = {
		cooldown_time = 3,
		explode_time = 3,
		blast_radius = 12,
		blast_pressure = 1000000,
		explode_sound = sounds_folder.Explode,
		fuse_sound = sounds_folder.Fuse
	},
	
	golden_bomb = {
		cooldown_time = 3,
		explode_time = 3,
		blast_radius = 15,
		blast_pressure = 2000000,
		explode_sound = sounds_folder.Explode,
		fuse_sound = sounds_folder.Fuse
	},
	
	c4 = {
		cooldown_time = 3,
		explode_time = 3,
		blast_radius = 8,
		blast_pressure = 1500000,
		explode_sound = sounds_folder.Explode
	},
	
	crewmate_tool = {
		cooldown_time = 5,
		explode_time = 5,
		blast_radius = 10,
		blast_pressure = 600000,
		explode_sound = sounds_folder.NoSound
	},
	
	hu_tao_bomb = {
		cooldown_time = 3,
		explode_time = 3,
		blast_radius = 20,
		blast_pressure = 10000000,
		explode_sound = sounds_folder.Explode
	},
	
	speed_coil = {
		speed_boost = 2,
		speed_for_smoke = 10,
		speed_up_sound = sounds_folder.SpeedUp
	},
	
	gravity_coil = {
		jump_height = 0.75,
		coil_sound = sounds_folder.GravityCoil
	},
	
	regen_coil = {
		regen_per_second = 3
	},
}



return statistics
