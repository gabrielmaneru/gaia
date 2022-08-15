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

includedir = {}
includedir["glfw"] = "Gaia/extern/glfw/include"
includedir["spdlog"] = "Gaia/extern/spdlog/include"
includedir["glad"] = "Gaia/extern/glad/include"
includedir["glm"] = "Gaia/extern/glm"

include "gaia/extern/glfw"
include "gaia/extern/spdlog"
include "gaia/extern/glad"
include "gaia/extern/glm"

project "gaia"
	location "gaia"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "-%{prj.name}/bin")
	objdir ("build/" .. outputdir .. "-%{prj.name}/obj")
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.c",  
		"%{prj.name}/src/**.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{includedir.glfw}",
		"%{includedir.spdlog}",
		"%{includedir.glad}",
		"%{includedir.glm}"
	}
	
	links 
	{
		"glfw",
		"spdlog",
		"glad",
		"glm"
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