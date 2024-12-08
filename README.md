# Game_LeadTheHordes_base
This is the repo in which I'll develop the basic of a new game I'm making.

Currently works only for Visual Studio 2022, but I'm working on compatibility with gmake2. SFML requires separate binary files for different compilers (including separate ones for each release of visual studio).

Eris Utility is an old mini-library of mine, done a few years ago - needs to be reworked.


### GCC compiling
If you decide to compile with GCC instead of Visual Studio, you need to compile with the version 13.1.0 of GCC. <br/>
This is due to the current SFML version. It's possible to recompile SFML out of compiling with CMAKE due to its <br/>
How to download previous version (MSYS):
- Mingw32:<br/>
  <pre>
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc-libs ||
  pacman -Rdd mingw-w64-ucrt-x86_64-gcc ||
  wget https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  wget https://repo.msys2.org/mingw/mingw32/mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst &&
  pacman -U mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-i686-gcc-libs-13.1.0-7-any.pkg.tar.zst ||
  rm mingw-w64-i686-gcc-13.1.0-7-any.pkg.tar.zst
  </pre>
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
