workspace "LeadTheHordes"

    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }
	
	
	project "Eris_Utility"
		kind "StaticLib"
		staticruntime "on"
		language "C++"
		cppdialect "C++17"
		systemversion "latest"
		
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
