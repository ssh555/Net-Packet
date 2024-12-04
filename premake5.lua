workspace "NetPacket"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)


-- 包含对应目录下的 premake5.lua


project "NetPacket"
	location "NetPacket"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "NetPacket/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	links 
	{ 

	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{

		}

		postbuildcommands
		{
		}

	filter "configurations:Debug"
		defines "NP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NP_DIST"
		optimize "On"

