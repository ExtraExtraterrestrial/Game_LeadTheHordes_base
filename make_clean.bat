
rem rmdir /s /q Eris_Utility\lib
rem rmdir /s /q Eris_Utility\obj
rmdir /s /q Eris_Utility\.vs

del /s Eris_Utility\*.vcxproj
del /s Eris_Utility\*.vcxproj.user
del /s Eris_Utility\*.vcxproj.filters
del /s Eris_Utility\*.sln

rem rmdir /s /q bin
rem rmdir /s /q obj
rmdir /s /q .vs


del /s *.vcxproj
del /s *.vcxproj.user
del /s *.vcxproj.filters
del /s *.sln


del /s Eris_Utility\Makefile
del /s LeadTheHordes\Makefile
del /s Makefile