// DrawCube.cpp
// Generate a Cube


#include "GL/glew.h"
#include <stdio.h>
#include <stdlib.h>
#include "GLFW/glfw3.h"
#include "Angel.h"

typedef  vec4  point4;
typedef  vec4  color4;

GLuint shader_programme;
GLuint vao;

GLint col;  // global location variable

int Index = 0;
const int NumVertices = 36;
point4 points[NumVertices];
color4 colors[NumVertices];

bool rootating = false;     // set rotation to false

//----------------------------------------------------------------------------

point4 vertices[8] = {
	point4(-0.5, -0.5, 0.5, 1.0),
	point4(-0.5, 0.5, 0.5, 1.0),
	point4(0.5, 0.5, 0.5, 1.0),
	point4(0.5, -0.5, 0.5, 1.0),
	point4(-0.5, -0.5, -0.5, 1.0),
	point4(-0.5, 0.5, -0.5, 1.0),
	point4(0.5, 0.5, -0.5, 1.0),
	point4(0.5, -0.5, -0.5, 1.0)
};

// RGBA olors
color4 vertex_colors[8] = {
	color4(0.0, 0.0, 0.0, 1.0),  // black
	color4(1.0, 0.0, 0.0, 1.0),  // red
	color4(1.0, 1.0, 0.0, 1.0),  // yellow
	color4(0.0, 1.0, 0.0, 1.0),  // green
	color4(0.0, 0.0, 1.0, 1.0),  // blue
	color4(1.0, 0.0, 1.0, 1.0),  // magenta
	color4(1.0, 1.0, 1.0, 1.0),  // white
	color4(0.0, 1.0, 1.0, 1.0)   // cyan
};

void
quad(int a, int b, int c, int d)
{
	points[Index] = vertices[a]; Index++;
	points[Index] = vertices[b]; Index++;
	points[Index] = vertices[c]; Index++;
	points[Index] = vertices[a]; Index++;
	points[Index] = vertices[c]; Index++;
	points[Index] = vertices[d]; Index++;
}
void
colorcube()
{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}

void init(void)
{
	colorcube();
	GLuint vert_shader, frag_shader;
	/* GL shader programme object [combined, to link] */

	// Specifiy the vertices for a triangle
	//GLfloat points[] = { -0.5, 0.5, 0.5, 0.5, 0.0, -0.5 };


	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Create a vertex array object

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// "attribute #0 is created from every 2 variables in the above buffer, of type
	// float (i.e. make me vec2s)"
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	// Load shaders and use the resulting shader program
	const char *vertex_shader = "#version 410\n"
		"in vec4 vPosition;"
		"void main () {"
		"	gl_Position = vPosition;"
		"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char *fragment_shader = "#version 410\n"
        "uniform vec4 color;"
		"out vec4 FragColor;"
		"void main () {"
        "   FragColor = color;" // uniform fragment color
		"}";

	vert_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader, 1, &vertex_shader, NULL);
	glCompileShader(vert_shader);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &fragment_shader, NULL);
	glCompileShader(frag_shader);
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, frag_shader);
	glAttachShader(shader_programme, vert_shader);
	glLinkProgram(shader_programme);
}

void mymouse(GLFWwindow* window, int button, int action, int mods) {
    // close window on button press
    if (action == GLFW_PRESS)  {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void mykey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // if key is pressed
    if (action == GLFW_PRESS) {
        Index++;    // increment index
//        // while index is within the vertex colors range (0 - 7)
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
            col = glGetUniformLocation(shader_programme, "color");  // retreive location of uniform variable
            vec4 m = vertex_colors[Index];  // define color
            glUniform4fv(col, 1, m);    // send color to shader
        }
    }
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{
	GLFWwindow *window = NULL;
	const GLubyte *renderer;
	const GLubyte *version;
	/* start GL context and O/S window using the GLFW helper library */
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	/* We must specify 3.2 core if on Apple OS X -- other O/S can specify
	anything here. I defined 'APPLE' in the makefile for OS X

	Remove the #ifdef #endif and play around with this - you should be starting
	an explicit version anyway, and some non-Apple drivers will require this too.
	*/
//#ifdef APPLE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif
	window = glfwCreateWindow(640, 640, "simple", NULL, NULL);

	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();
	renderer = glGetString(GL_RENDERER); /* get renderer string */
	version = glGetString(GL_VERSION);	 /* version as a string */
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	init();

	do{
        glClear(GL_COLOR_BUFFER_BIT);     // clear the window
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);    // draw the points
		/* update other events like input handling */
        
        glfwSetMouseButtonCallback(window, mymouse);    // mouse callback
        glfwSetKeyCallback(window, mykey);  // keyboard callback
        
		glfwPollEvents();
		glfwSwapBuffers(window);
	} while (!glfwWindowShouldClose(window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;

}
