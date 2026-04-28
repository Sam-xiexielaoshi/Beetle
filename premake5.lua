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
IncludeDir["yaml_cpp"] = "Beetle/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Beetle/vendor/ImGuizmo"

group "Dependencies"
	include "Beetle/vendor/GLFW"
	include "Beetle/vendor/Glad"
	include "Beetle/vendor/imgui"
	include "Beetle/vendor/yaml-cpp"

group ""

include "Beetle/vendor/GLFW"
include "Beetle/vendor/Glad"
include "Beetle/vendor/imgui"

project "Beetle"
	location "Beetle"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
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
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}",
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:Beetle/vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }
	filter {}

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
		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "BT_Release"
		runtime "Release"
		optimize "On"
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
	filter "configurations:DIST"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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
	staticruntime "off"

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
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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