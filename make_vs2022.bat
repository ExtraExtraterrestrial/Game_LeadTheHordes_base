rmdir /s /q Eris_Utility\.vs
del /s Eris_Utility\*.vcxproj
del /s Eris_Utility\*.vcxproj.user
del /s Eris_Utility\*.vcxproj.filters
del /s Eris_Utility\*.sln

rmdir /s /q .vs
del /s *.vcxproj
del /s *.vcxproj.user
del /s *.vcxproj.filters
del /s *.sln


premake\premake5.exe vs2022
