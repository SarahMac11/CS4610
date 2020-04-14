# Assignment 1

## Part A: 
simple.cpp run on Xcode Assignment1. Added /usr/local/include to the Search Paths > Header Search Paths and OpenGL.framework, libGLEW.2.1.0.dylib, and libglfw.3.3.dylib to Link Binary With Libraries.
 
## Part B: run example1.cpp program
 

## Part C: Run RotateCube.cpp, fshder36.glsl, vshader36.glsl, InitShader.cpp, and include.zip
(mat_for_mac.h since using a Mac):
### Added headers to InitShader.cpp:
#include "GL/glew.h"
#include "GLFW/glfw3.h" 

Changed the Angel.h include from “mat.h” to “mat_for_mac.h”
### Had to put the exact route of the shaders into RotateCube.cpp:
GLuint program = InitShader("/Users/Sarah/Desktop/Project1/vshader36.glsl", "/Users/Sarah/Desktop/Project1/fshader36.glsl");


## Part D: Modify Part A to display a square instead of triangle and in a different color.
### Changed simple.cpp (lines 20, 51, and 116):
GLfloat points[] = { -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5 };
"	FragColor = vec4( 0.0, 0.0, 1.0, 1.0 );"
glDrawArrays(GL_TRIANGLES, 0, 6 );

