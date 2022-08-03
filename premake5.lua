workspace "gaia"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"debug", 
		"release"
	}

	startproject "gaia"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

project "gaia"
	location "gaia"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "-%{prj.name}/bin")
	objdir ("build/" .. outputdir .. "-%{prj.name}/obj")

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/extern"
	}
	
	links 
	{
	}
	
	filter "system:windows"
		systemversion "latest"
		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}
		

	filter "configurations:debug"
		symbols "On"
				
	filter "configurations:release"
		optimize "On"