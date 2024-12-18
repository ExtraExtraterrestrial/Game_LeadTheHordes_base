workspace "LeadTheHordes"

    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }
	
	
	project "Eris_Log"
		kind "StaticLib"
		staticruntime "off"
		language "C++"
		cppdialect "C++17"
		systemversion "latest"
		
		targetdir (outputdir)
		objdir ("obj/" .. outputdirname)


		defines { "LOG_DO_NOT_AUTOSTART" }
		
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
