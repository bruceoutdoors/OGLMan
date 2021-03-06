OGLMan
======

OGLMan ("OpenGL Manager") is a bunch of convenience classes that ease the management of shaders, buffers and meshes in the modern shader based OpenGL. I created these to help me understand how OpenGL works. 

This program is tested with Windows 8.1 (MinGW 4.8) and Manjaro Linux XFCE.

Uses modified Obj reader code from http://www.opengl-tutorial.org/

### Dependencies
- SFML 2.1 for the render window 
- GLEW 1.10.1 (MinGW version) to manage OpenGL function calls.
- Qt Creator 3.1.1, though not using Qt
- GLM 0.9.5.4 (OpenGL Mathematics)
- SFGUI 0.2.3 (modified version)
- C++11 compiler

The dependencies for Windows MinGW 4.8 are bundled together with the project files. I did this because it's convenient, and the SFGUI here has been slightly tampered with; It will fail if you use your own build. 

### Setup Instructions
After the inital configuring part is done in Qt Creator, 

1. go under the "Projects" tab
2. under "Build | Run" select "Run" to change the run settings
3. under "Run", remove "\build" at the end of "Working directory" 

This will allow you to run your application from Qt Creator. The "build" folder is also where you place your dependencies. Take note that during deployment, the "shaders" and "resource" directory should be copied to the executable's directory.

### Background and Credits

This program started off as a fork of Jamie King's modern OpenGL tutorials (http://bit.ly/1t2Rxde). Although the design of the program is now completely different, you find pieces of Jamie's finger prints inside, especially in the primitives. 

### License
I don't care what you do with it, since there are better libraries that do this sort of stuff way better. However, if you actually somehow manage to find this useful, do drop me a love letter and say thanks (:
