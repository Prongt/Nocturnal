workspace "Nocturnal"
    architecture "x64"
	startproject "Sandbox"
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
IncludeDir["imgui"] = "Nocturnal/vendor/imgui"
IncludeDir["glm"] = "Nocturnal/vendor/glm"

group "Dependencies"
	include "Nocturnal/vendor/GLFW"
	include "Nocturnal/vendor/GLAD"
	include "Nocturnal/vendor/imgui"
group ""


    
project "Nocturnal"
    location "Nocturnal"
    kind "SharedLib"
    language "C++"
	staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "NocturnalPrecompiledHeaders.h"
	pchsource "Nocturnal/src/NocturnalPrecompiledHeaders.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}
	
	links{
		"GLFW",
		"GLAD",
		"imgui",
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
        ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
    }

    filter "configurations:Debug"
		defines "NOC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NOC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NOC_DIST"
		runtime "Release"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Nocturnal/src",
		"Nocturnal/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nocturnal"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"

		defines
		{
			"NOC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NOC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NOC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NOC_DIST"
		runtime "Release"
		optimize "On" 