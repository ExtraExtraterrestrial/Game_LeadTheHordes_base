# Game_LeadTheHordes_base
This is the repo in which I'll develop the minimal viable product version of a game I'm making.

Currently works for Visual Studio and gmake2. Not tested on linux!
SFML requires separate binary files for different compilers (including separate ones for each release of visual studio and GCC).

Eris Utility is an old mini-library of mine, done a few years ago - needs to be reworked.


### GCC compiling
If you decide to compile with GCC instead of Visual Studio, you need to compile with the version 13.1.0 of GCC. <br/>
I'm seriously pondering CMake for this reason <br/>
This is due to the current SFML version which was compiled with that specific version of GCC. <br/>
How to download previous version (MSYS):
<!-- - Mingw32:<br/>
  <pre>
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc-libs ||
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc ||
  wget https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  wget https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst
  </pre-->
- Mingw64:<br/>
  <pre>
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc-libs ||
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc ||
  wget https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  wget https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-gcc-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-x86_64-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-x86_64-gcc-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-x86_64-gcc-libs-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-x86_64-gcc-13.1.0-7-any.pkg.tar.zst
  </pre>
