# ExpansionGameEngine

Expansion Game Engine is a 3D game engine under development.

## Target List
 - [ ] Multi-API rendering (OpenGL, Vulkan, and DirectX11/12 if I want to export to XBox)
   - [x] OpenGL 3/4
   - [ ] Vulkan (In priority to D3D, soon to be started)
   - [ ] Direct3D
 - [x] Going PBR
 - [x] Lightweight build (<30MB for all engine files) & SDK (<300MB for the whole sdk)
 - [x] Light and Shadow fully realtime
 - [x] Deffered rendering
 - [x] Cross-Platorm :
   - [x] Windows
   - [x] Linux
   - [ ] Console
     - [ ] Switch
     - [ ] PS4
     - [ ] XBox
   - [ ] Android
   - [ ] MacOS (last priority)
 - [ ] Optimise as f\*ck -> I want to have a very well optimised engine to run everywhere
 - [ ] An easy to understand & easy to use engine
     - [ ] JS **and** Python Scripting
     - [ ] Powerful all-in-one editor
     - [ ] Well written documentation

## Screenshots
Here you have some screenshots I took from the last demo I've made.

![alt text](screenshots/EXPGE_Screen_1.PNG)
![alt text](screenshots/EXPGE_Screen_2.PNG)

Some tests on instanciated meshes and rotations issues (now solved =° ), and GUI System

![alt text](screenshots/EXPGE_Screen_3.PNG)

A little Maze Generator I've built with EXPGE

![alt text](screenshots/EXPGE_Screen_4.PNG)
![alt text](screenshots/EXPGE_Screen_5.PNG)
![alt text](screenshots/EXPGE_Screen_6.PNG)

FBX to MSH convertion tool

![alt text](screenshots/EXPGE_Screen_7.PNG)

First demo of my PBR impl

![alt_text](screenshots/EXPGE_Screen_8.PNG)

## TODO List

 - [x] Check compatibility with linux (and make it compatible)
 - [x] Reduce RAM usage
 - [x] Impl. Shadows to Raindrop Renderer
   - [ ] Improve these (for instance, better PCF)
 - [x] Fix Debug rendering (Combine forward rendering with deffered)
 - [x] Rebuild point-lighting system (--> Lighting in volumes)
 - [x] Better management of ressources (especially with texture) --> I'll make a MaterialLibrary system to manage all of that, it will be transparent for the final user, but it will optimise a lot GPU memory usage
 - [x] Fix window resize
 - [x] Proprer input manager
 - [x] Custom shaders
 - [ ] ExpansionMath Cleanup
   - [x] Rewrite vectors (vec3X & vec2X)
   - [x] Add matrices support
   - [ ] Add Quaternion support
   - [x] Use SIMD operations
 - [x] Use smartptr when possible
 - [ ] Consistent error handling
 - [ ] Fix the error when reducing the window
 - [ ] Font Rendering on GUI System
 
## Dependencies
  - OpenAL Soft (by @Kcat)
  - GLFW3
  - OpenGL
  - GLAD
  - GLEW
  - libsndfile1
  - Bullet Physics
  - ASSIMP (For tools)
  - Qt (For tools)
  - Jsoncpp
  - FreeType2
 
NB1 : All libs that are precompiled and in this repo are compiled for Windows x64. If you want to compile this engine for Windows x86 you need to do it yourself. If you want to compile this engine for linux you'll need to install all the dependencies using your package manager.
 
NB2 : CMakeLists.txt are specially made for Linux, if you want to compile the engine for Windows, you can just use my Visual Studio solution (I usually update it at each VS major release, for now it is a VS2019 solution).
 
## License
This project is under CC-BY-NC-SA license.

For any question please contact me.
