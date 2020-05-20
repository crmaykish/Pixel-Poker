# PIXEL POKER

## Build Dependencies
1. CMake
2. [GoogleTest](https://github.com/google/googletest)
3. SDL2
4. SDL2_image
5. SDL2_ttf

On Debian/Ubuntu: `apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl-ttf-dev`

## Missing Features
 - Variable betting amounts
 - Reset on running out of money
 - Sound effects
 - Shuffle and dealing animations
 - Highlight win type and amount
 - Track some basic statistics (win rate, bet amounts, number of hands, etc)
 - Final write-up on lessons learned, mistakes made, future ideas, etc

## Architecture Ideas
- Combine collections of commands instead of having to attach every one separately, e.g. all buttons will have an update handler and a clicked callback.
- Cache textures instead of loading from file every time, see if it helps CPU usage

## Bugs
- Sometimes drawing only four cards
- a ton of memory leaks

## Todo List
