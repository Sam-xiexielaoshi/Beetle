workspace "Beetle"
	architecture "x64"
	startproject "Stag"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directoried reative to root folder 
IncludeDir = {}
IncludeDir["GLFW"] = "Beetle/vendor/GLFW/include"
IncludeDir["Glad"] = "Beetle/vendor/Glad/include"
IncludeDir["ImGui"] = "Beetle/vendor/imgui"
IncludeDir["glm"] = "Beetle/vendor/glm"
IncludeDir["stb_image"] = "Beetle/vendor/stb_image"
IncludeDir["entt"] = "Beetle/vendor/entt/include"

group "Dependencies"
	include "Beetle/vendor/GLFW"
	include "Beetle/vendor/Glad"
	include "Beetle/vendor/imgui"

group ""

include "Beetle/vendor/GLFW"
include "Beetle/vendor/Glad"
include "Beetle/vendor/imgui"

project "Beetle"
	location "Beetle"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "btpch.h"
	pchsource "Beetle/src/btpch.cpp"

	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines
		{
			"BT_PLATFORM_WINDOWS",
			"BT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:DIST"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"Beetle/vendor/spdlog/include",
		"Beetle/src",
		"Beetle/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Beetle"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines
		{
			"BT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"

project "Stag"
	location "Stag"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"Beetle/vendor/spdlog/include",
		"Beetle/src",
		"Beetle/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Beetle"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines
		{
			"BT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"