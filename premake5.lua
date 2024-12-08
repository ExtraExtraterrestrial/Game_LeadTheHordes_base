workspace "LeadTheHordes"

    outputdirname = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}_" .. _ACTION
    outputdir = "bin/" .. outputdirname

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
        staticruntime "on"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        systemversion "latest"


        
        if os.target() == "windows" then
            if _ACTION == "vs2022" then
                sfmldir = "SFML/Windows_vs22"
            elseif _ACTION == "vs2019" then
                sfmldir = "SFML/Windows_vs19"
            elseif _ACTION == "gmake2" then
                sfmldir = "SFML/Windows_GCC"
            else
                print("Type of project not supported")
            end

            
        elseif os.target() == "linux" then
            sfmldir = "SFML/Linux_GCC"

        elseif os.target() == "macosx" then
            print("\n==================================================\nMac not supported yet!\n==================================================\n")

        else
            print("\n==================================================\nSystem not supported!\n==================================================\n")
        end

        
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
            sfmldir .. "/lib"
        }
        

        links {
            "Eris_Utility"
        }

        includedirs {
            "LeadTheHordes/src",
            sfmldir .. "/include",
            "Eris_Utility/include"
        }

        pchheader "Hordes_pch.h"
        pchsource "LeadTheHordes/src/Hordes_pch.cpp"
        
        postbuildcommands { "{COPYDIR} configs ../" .. outputdir .. "/configs"}

        filter "configurations:Debug"
            defines "HORDES_DEBUG"
            runtime "Debug"
            symbols "On"
            
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-d-2.dll ../" .. outputdir }
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-d-2.dll ../" .. outputdir }

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

            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-2.dll ../" .. outputdir }
            
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
            
            
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-2.dll ../" .. outputdir}
            postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-2.dll ../" .. outputdir }


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


    
