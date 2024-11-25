workspace "LeadTheHordes"

print(_ACTION) -- finish checking for action and figure out static sfml


    architecture "x64"
    startproject "LeadTheHordes"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    group "dependencies"
        include "Eris_Utility"
    group ""


    project "LeadTheHordes"
        location "LeadTheHordes"
        staticruntime "on" -- this might cause issues later with dynamic sfml
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        systemversion "latest"

        outputdirname = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}_" .. _ACTION
        outputdir = "bin/" .. outputdirname
        
        linkoptions { "-IGNORE:4099" }

        targetdir (outputdir)
        objdir ("obj/" .. outputdirname)

        files {
            "LeadTheHordes/src/**.h",
            "LeadTheHordes/src/**.hpp",
            "LeadTheHordes/src/**.cpp"
        }
        
        libdirs {
            "Eris_Utility/lib/" .. outputdirname,
            "SFML/lib"
        }
        

        links {
            "Eris_Utility"
        }

        includedirs {
            "LeadTheHordes/src",
            "SFML/include",
            "Eris_Utility/include"
        }

        pchheader "Hordes_pch.h"
        pchsource "LeadTheHordes/src/Hordes_pch.cpp"
        
        postbuildcommands { "{COPYDIR} configs ../" .. outputdir .. "/configs"}

        filter "configurations:Debug"
            defines "HORDES_DEBUG"
            runtime "Debug"
            symbols "On"
            
            prebuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir }
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-d-2.dll ../" .. outputdir }
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-d-2.dll ../" .. outputdir }
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-d-2.dll ../" .. outputdir }
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-d-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "winmm",
                "opengl32",
                "freetype",
                "gdi32",
                --[[ these are for audio ]]
                "openal32",
                "flac",
                "vorbisenc",
                "vorbisfile",
                "vorbis",
                "ogg",
                --[[ SFML ]]
                "sfml-system-d",
                "sfml-window-d",
                "sfml-graphics-d",
                "sfml-audio-d"
            }

        filter "configurations:Release"
            defines "HORDES_RELEASE"
            runtime "Release"
            optimize "On"
            
            prebuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "opengl32",
                "freetype",
                "winmm",
                "gdi32",
                --[[ these are for audio ]]
                "flac",
                "vorbisenc",
                "vorbisfile",
                "vorbis",
                "ogg",
                --[[ SFML ]]
                "sfml-system",
                "sfml-window",
                "sfml-graphics",
                "sfml-audio"
            }

        filter "configurations:Dist"
            defines "HORDES_DIST"
            runtime "Release"
            optimize "On"
            
            
            prebuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-2.dll ../" .. outputdir}
            prebuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "opengl32",
                "freetype",
                "winmm",
                "gdi32",
                --[[ these are for audio ]]
                "flac",
                "vorbisenc",
                "vorbisfile",
                "vorbis",
                "ogg",
                --[[ SFML ]]
                "sfml-system",
                "sfml-window",
                "sfml-graphics",
                "sfml-audio"
            }

    
        filter ""


    
