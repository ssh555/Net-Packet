workspace "NetPacket"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "StructFileGenerator"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)


-- 包含对应目录下的 premake5.lua


project "NetPacket"
	location "NetPacket"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nppch.h"
	pchsource "NetPacket/src/nppch.cpp"

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

	defines
	{
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"NP_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/StructFileGenerator")
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

project "StructFileGenerator"
	location "StructFileGenerator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NetPacket/src"
	}

	links
	{
		-- 项目链接 -> 项目依赖项
		"NetPacket"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{

		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SF_DIST"
		optimize "On"