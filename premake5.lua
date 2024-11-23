workspace "LeadTheHordes"
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
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        systemversion "latest"

        outputdirname = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}"
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
            "SFML/lib",
            "Eris_Utility/lib/" .. outputdirname -- Eris_Utility has different outputs depending on build, change its premake if needed
        }

        links {
            "Eris_Utility",
            "Eris_Utility.lib"
        }

        includedirs {
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
            
            postbuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-d-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "winmm.lib",
                "opengl32.lib",
                "freetype.lib",
                "gdi32.lib",
                --[[ these are for audio ]]
                "openal32.lib",
                "flac.lib",
                "vorbisenc.lib",
                "vorbisfile.lib",
                "vorbis.lib",
                "ogg.lib",
                --[[ SFML ]]
                "sfml-system-d.lib",
                "sfml-window-d.lib",
                "sfml-graphics-d.lib",
                "sfml-audio-d.lib"
            }

        filter "configurations:Release"
            defines "HORDES_RELEASE"
            runtime "Release"
            optimize "On"
            
            
            postbuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "opengl32.lib",
                "freetype.lib",
                "winmm.lib",
                "gdi32.lib",
                --[[ these are for audio ]]
                "flac.lib",
                "vorbisenc.lib",
                "vorbisfile.lib",
                "vorbis.lib",
                "ogg.lib",
                --[[ SFML ]]
                "sfml-system.lib",
                "sfml-window.lib",
                "sfml-graphics.lib",
                "sfml-audio.lib"
            }

        filter "configurations:Dist"
            defines "HORDES_DIST"
            runtime "Release"
            optimize "On"
            
            
            postbuildcommands { "{COPYFILE} ../SFML/bin/openal32.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-system-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-window-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-graphics-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../SFML/bin/sfml-audio-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "opengl32.lib",
                "freetype.lib",
                "winmm.lib",
                "gdi32.lib",
                --[[ these are for audio ]]
                "flac.lib",
                "vorbisenc.lib",
                "vorbisfile.lib",
                "vorbis.lib",
                "ogg.lib",
                --[[ SFML ]]
                "sfml-system.lib",
                "sfml-window.lib",
                "sfml-graphics.lib",
                "sfml-audio.lib"
            }

    
        filter ""


    
