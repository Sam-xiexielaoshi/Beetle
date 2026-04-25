include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Beetle"
	architecture "x86_64"
	startproject "stag"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Beetle/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Beetle/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Beetle/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Beetle/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Beetle/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Beetle/vendor/entt/include"

group "Dependencies"
	include "vendor/premake"
	include "Beetle/vendor/GLFW"
	include "Beetle/vendor/Glad"
	include "Beetle/vendor/imgui"
group ""

include "Beetle"
include "Sandbox"
include "Stag"