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
	location "Source"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nppch.h"
	pchsource "Source/%{prj.name}/Private/nppch.cpp"

	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Source/**.hpp"
	}

	-- 排除特定模式的文件
	removefiles
	{
		"Source/**/Struct/**.h",
		"Source/**/Config/**.np"
	}

	includedirs
	{
		"Source/%{prj.name}/Public",
		-- "Source/%{prj.name}/Public/Json/include/include/nlohmann",
		"Source/%{prj.name}/Public/Json/include/single_include/nlohmann",
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
		
		disablewarnings { "4251" }  -- 禁用 C4251 警告

		postbuildcommands
		{
			-- 创建目标文件夹（如果不存在）
			("{MKDIR} ../bin/" .. outputdir .. "/StructFileGenerator"),
			-- 复制目标文件到目标文件夹
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
		"Source/NetPacket/Public"
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