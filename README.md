# Game_LeadTheHordes_base
This is the repo in which I'll develop the *minimal viable product* version of a game I'm making.

## Building
To the CMake project, I suggest using the following commands:
<pre>
cmake -B build
cmake --build build
</pre>

### Technologies needed:
| Technology | Description |
|------------|-------------------------------------------------|
| CMake      | Required pre-install - https://cmake.org/download/ |
| SFML       | Automatically fetched from the [SFML repo](https://github.com/SFML/SFML.git) when building the project through CMake |
| Eris Log   | Already included. <br/> An old library of my own that has never been published on its own. <br/> Uses a lot of C-style coding for optimization purposes. |
