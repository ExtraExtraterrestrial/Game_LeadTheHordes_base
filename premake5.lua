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


    project "LeadTheHordes"
        location "LeadTheHordes"
        staticruntime "off"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        systemversion "latest"

        defines "SFML_STATIC"

        group "dependencies"
            include "Eris_Utility"
        group ""


        sfmlLibPrefix = ""
        if os.target() == "windows" then
            if _ACTION == "vs2022" then
                sfmldir = "SFML/Windows_vs22"
            elseif _ACTION == "vs2019" then
                sfmldir = "SFML/Windows_vs19"
            elseif _ACTION == "gmake2" then
                sfmldir = "SFML/Windows_GCC"
                sfmlLIBprefix = "lib"
            else
                print("Type of project not supported")
            end

            
        elseif os.target() == "linux" then
            sfmldir = "SFML/Linux_GCC"
            sfmlLibPrefix = "lib"

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
            
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir }
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-d-2.dll ../" .. outputdir }
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-d-2.dll ../" .. outputdir }
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-d-2.dll ../" .. outputdir }
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-d-2.dll ../" .. outputdir }

            links {
                --[[ SFML dependencies ]]
                "winmm",
                "opengl32",
                sfmlLibPrefix .. "freetype",
                "gdi32",
                --[[ these are for audio ]]
                sfmlLibPrefix .. "openal32",
                sfmlLibPrefix .. "flac",
                sfmlLibPrefix .. "vorbisenc",
                sfmlLibPrefix .. "vorbisfile",
                sfmlLibPrefix .. "vorbis",
                sfmlLibPrefix .. "ogg",
                --[[ SFML ]]
                sfmlLibPrefix .. "sfml-system-s-d",
                sfmlLibPrefix .. "sfml-window-s-d",
                sfmlLibPrefix .. "sfml-graphics-s-d",
                sfmlLibPrefix .. "sfml-audio-s-d"
            }

        filter "configurations:Release"
            defines "HORDES_RELEASE"
            runtime "Release"
            optimize "On"

            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-2.dll ../" .. outputdir }
            
            links {
                --[[ SFML dependencies ]]
                "opengl32",
                sfmlLibPrefix .. "freetype",
                "winmm",
                "gdi32",
                --[[ these are for audio ]]
                sfmlLibPrefix .. "openal32",
                sfmlLibPrefix .. "flac",
                sfmlLibPrefix .. "vorbisenc",
                sfmlLibPrefix .. "vorbisfile",
                sfmlLibPrefix .. "vorbis",
                sfmlLibPrefix .. "ogg",
                --[[ SFML ]]
                sfmlLibPrefix .. "sfml-system-s",
                sfmlLibPrefix .. "sfml-window-s",
                sfmlLibPrefix .. "sfml-graphics-s",
                sfmlLibPrefix .. "sfml-audio-s"
            }

        filter "configurations:Dist"
            defines "HORDES_DIST"
            runtime "Release"
            optimize "On"
            
            
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/openal32.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-system-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-window-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-graphics-2.dll ../" .. outputdir}
            -- postbuildcommands { "{COPYFILE} ../" .. sfmldir .. "/bin/sfml-audio-2.dll ../" .. outputdir }


            links {
                --[[ SFML dependencies ]]
                "opengl32",
                sfmlLibPrefix .. "freetype",
                "winmm",
                "gdi32",
                --[[ these are for audio ]]
                sfmlLibPrefix .. "openal32",
                sfmlLibPrefix .. "flac",
                sfmlLibPrefix .. "vorbisenc",
                sfmlLibPrefix .. "vorbisfile",
                sfmlLibPrefix .. "vorbis",
                sfmlLibPrefix .. "ogg",
                --[[ SFML ]]
                sfmlLibPrefix .. "sfml-system-s",
                sfmlLibPrefix .. "sfml-window-s",
                sfmlLibPrefix .. "sfml-graphics-s",
                sfmlLibPrefix .. "sfml-audio-s"
            }

    
        filter ""


    
