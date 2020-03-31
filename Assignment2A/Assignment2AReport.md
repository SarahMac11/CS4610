Sarah McLaughlin – skm9b3
14237628
5 March 2020
# Assignment 2A

## Part A:
Included OpenGL.framework, GLUT.framework, libGLEW.2.1.0.dylib and libglfw.3.3.dylib to Build Phases > Link Binary With Libraries and added “/usr/local/include” to Build Settings > Search Paths.
### Commented out ifdef APPLE (lines 131-136:
//#ifdef APPLE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif
 
Included OpenGL.framework, GLUT.framework, libGLEW.2.1.0.dylib and libglfw.3.3.dylib to Build Phases > Link Binary With Libraries and added “/usr/local/include” to Build Settings > Search Paths.

### Commented out ifdef APPLE (lines 131-136:
//#ifdef APPLE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif


## Part B:

Code alterations:
In angel.h: #include "mat_for_mac.h" – Because using Mac OS

### Commented out ifdef APPLE (lines 142-147):
//#ifdef APPLE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif

### Global location variable (line 17): 
GLint col;  // global location variable

### Include fragment shader uniform variable (lines 104 – 110):
const char *fragment_shader = "#version 410\n"
"uniform vec4 color;"
	"out vec4 FragColor;"
	"void main () {"
        	"	FragColor = color;"	// uniform fragment color
"}";

### The mymouse callback when right mouse button is clicked, application exits (lines 124 – 129):
void mymouse(GLFWwindow* window, int button, int action, int mods) {
// close window on button press
    	if (action == GLFW_PRESS)  {
        		glfwSetWindowShouldClose(window, GL_TRUE);
   	}
}

### The mykey callback used to change color of the box when key is clicked, and follows the color change referencing vertex_colors array of RGBA colors (lines 131 – 165):
void mykey(GLFWwindow* window, int key, int scancode, int action, int mods) {
// if key is pressed
    	if (action == GLFW_PRESS) {
        		Index++;    // increment index
        		// while index is within the vertex colors range (0 - 7)
        		if (Index > 7) {
            			Index = 0;  // reset index
            			glClear(GL_COLOR_BUFFER_BIT);     // clear the window
            			glUseProgram(shader_programme);
            			col = glGetUniformLocation(shader_programme, "color");  // retreive location of uniform variable
            			vec4 m = vertex_colors[Index];  // define color
            			glUniform4fv(col, 1, m);    // send color to shader
        		} else {
            			glClear(GL_COLOR_BUFFER_BIT);     // clear the window
            			glUseProgram(shader_programme);
            			col = glGetUniformLocation(shader_programme, "color"); 
            			vec4 m = vertex_colors[Index];  // define color
            			glUniform4fv(col, 1, m);    // send color to shader
        		}
   	}
}

### Mouse and key callbacks added to main.cpp (lines 203 – 204):
glfwSetMouseButtonCallback(window, mymouse);    // mouse callback
glfwSetKeyCallback(window, mykey);  // keyboard callback
   
   

