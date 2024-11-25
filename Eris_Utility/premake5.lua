project "Eris_Utility"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	architecture "x86_64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	outputdirname = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}_" .. _ACTION
	outputdir = "lib/" .. outputdirname

	targetdir (outputdir)
	objdir ("obj/" .. outputdirname)

	files {
		"include/%{prj.name}/**.h",
		"src/**.cpp",
		"src/**.tpp"
	}

	includedirs {
		"include"
	}


	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		optimize "On"
		runtime "Release"
