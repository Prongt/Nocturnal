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
IncludeDir["stb_image"] = "Nocturnal/vendor/stb_image"

group "Dependencies"
	include "Nocturnal/vendor/GLFW"
	include "Nocturnal/vendor/GLAD"
	include "Nocturnal/vendor/imgui"
group ""


    
project "Nocturnal"
    location "Nocturnal"
	kind "StaticLib"
	
	language "C++"
	cppdialect "C++17"

	staticruntime "on"
	

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "NocturnalPrecompiledHeaders.h"
	pchsource "Nocturnal/src/NocturnalPrecompiledHeaders.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}
	defines{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"

	}
	
	links{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines{
            "NOC_PLATFORM_WINDOWS",
            "NOC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
	cppdialect "C++17"

	staticruntime "On"

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