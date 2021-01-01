workspace "Nocturnal"
    architecture "x64"

    configurations
	{
		"Debug",
		"Release",
		"Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nocturnal/vendor/GLFW/include"
IncludeDir["GLAD"] = "Nocturnal/vendor/GLAD/include"
include "Nocturnal/vendor/GLFW"
include "Nocturnal/vendor/GLAD"

    
project "Nocturnal"
    location "Nocturnal"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "NocturnalPrecompiledHeaders.h"
	pchsource "Nocturnal/src/NocturnalPrecompiledHeaders.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}
	
	links{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines{
            "NOC_PLATFORM_WINDOWS",
            "NOC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }
    postbuildcommands{
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    }

    filter "configurations:Debug"
		defines "NOC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "NOC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "NOC_DIST"
		buildoptions "/MD"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nocturnal/vendor/spdlog/include",
		"Nocturnal/src"
	}

	links
	{
		"Nocturnal"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NOC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NOC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "NOC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "NOC_DIST"
		buildoptions "/MD"
		optimize "On" 