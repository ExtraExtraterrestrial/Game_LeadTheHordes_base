# Game_LeadTheHordes_base
This is the repo in which I'll develop the *minimal viable product* version of a game I'm making.

## Building
To create and run the CMake project, I suggest using the following commands in the project's directory:
<pre>
cmake -B build -G "Visual Studio 17 2022"
cmake --build build
</pre>
After using these commands, you'll find the solution folder in build/.

I'm developing this game with windows/vs2022 as the primary platform in mind. Building for other platforms might lead to problems, but it's possible to do by changing the generator variable `-G "Visual Studio 17 2022"` to one that can be found here: [https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).

### Technologies needed:
| Technology | Description |
|------------|-------------------------------------------------|
| CMake      | Required pre-install - https://cmake.org/download/ |
| SFML       | Automatically fetched from the [SFML repo](https://github.com/SFML/SFML.git) when building the project through CMake |
| Eris Log   | Already included. <br/> An old library of my own that has never been published on its own. |
