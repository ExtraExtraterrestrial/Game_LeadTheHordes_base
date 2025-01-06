rmdir /s /q .\build 2> nul

cmake -B build
cmake --build build