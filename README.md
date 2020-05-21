# PIXEL POKER

## Build Dependencies
1. CMake
2. [GoogleTest](https://github.com/google/googletest)
3. SDL2
4. SDL2_image
5. SDL2_ttf
6. SDL2_mixer

On Debian/Ubuntu: `apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`

## Missing Features
 - Reset on running out of money
 - Add a "repeat last bet" quick deal option to deal button on game over
 - Sound effects
 - Shuffle and dealing animations
 - Variable resolution and full screen support
 - Controller support
 - Final write-up on lessons learned, mistakes made, future ideas, etc

## Architecture Ideas
- Combine collections of commands instead of having to attach every one separately, e.g. all buttons will have an update handler and a clicked callback.
- Need a good way to trigger sounds from all over the application
    - Don't want it in the gamestate
    - Register sounds to UI events
        - Doesn't solve non-UI sounds
    - Sounds need to be playable when gamestate changes
    - Maybe a combination of sound-playing event handlers is enough?
    - How about music? Register a sound command to the gamestate? have it call it during update()?
    - Maximum dependency injection
    - Is it ok to have sounds on UI events and from the game state? Any potential for conflict?
    - Or tie them all to scenes? Haven't really done anything with scenes yet

    - Start with onclick sound effects
    - Then register sound events to the gamestate

## Bugs

## Todo List
- add a default font and make the set method optional
- add default textures too