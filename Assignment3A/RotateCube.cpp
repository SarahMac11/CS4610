// RotateCube.cpp
// Generate a rotating cube on a solid background

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "InitShader.h"
#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/normal.hpp"


GLuint vao;
int Index = 0;
GLuint program;
const int NumVertices = 36;
glm::vec4 points[NumVertices];
glm::vec4 colors[NumVertices];

glm::mat4 model;    // model
glm::vec3 eye(0.0f, 0.0f, 2.0f);
glm::vec3 at(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0, 1.0f, 0.0f);
glm::mat4 view;     // view

glm::mat4 Projection;   // projection
glm::mat4 mvp;          // mvp

// model
float modelValDefault = 1.0f;
const glm::mat4 modelDefault = glm::mat4(modelValDefault);
glm::mat4 gModel = modelDefault;    // default model

float fovValDefault = 45.0f;
float fov = fovValDefault;  // default field of view
float fovOffset = 10.0f;

// aspect
float aspectValDefault = 1.0f;
float aspectDelta = 0.2f;
float aspect = aspectValDefault;    // set default aspect

// near clipping plane
float ncpValDefault = 0.1f;
float ncpDelta = 0.5f;
float ncp = ncpValDefault;    // set default near clipping plane
// far clipping plane
float fcpValDefault = 100.0f;
float fcpDelta = 10.0f;
float fcp = fcpValDefault;      // set default far clipping plane

float rotateValDelta = 5.0f;   // rotate default

// scales and offsets
float modScale = 1.0f;
float tranScale = 0.1f;
float offset = 0.1f;    // zoom in and out offset

float near = 0.1f;
float far = 100.f;

bool isPressed = false;     // set to false
double oldX = 0.0f;
double oldY = 0.0f;

int hrotate = 0;
int vrotate = 0;
//----------------------------------------------------------------------------

glm::vec4 vertices[8] = {
	glm::vec4(-0.5, -0.5, 0.5, 1.0),
	glm::vec4(-0.5, 0.5, 0.5, 1.0),
	glm::vec4(0.5, 0.5, 0.5, 1.0),
	glm::vec4(0.5, -0.5, 0.5, 1.0),
	glm::vec4(-0.5, -0.5, -0.5, 1.0),
	glm::vec4(-0.5, 0.5, -0.5, 1.0),
	glm::vec4(0.5, 0.5, -0.5, 1.0),
	glm::vec4(0.5, -0.5, -0.5, 1.0)
};

glm::vec4 vertex_colors[8] = {
	glm::vec4(0.0, 0.0, 0.0, 1.0),  // black
	glm::vec4(1.0, 0.0, 0.0, 1.0),  // red
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(0.0, 0.0, 1.0, 1.0),  // blue
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 1.0, 1.0, 1.0),  // white
	glm::vec4(0.0, 1.0, 1.0, 1.0)   // cyan
};

enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };


GLuint  mvpi; 

void quad(int a, int b, int c, int d)
{
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
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

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	// Load shaders and use the resulting shader program
	program = InitShader("/Users/Sarah/Desktop/Computer_Graphics/Assignment3A/Assignment3A/vshader36.glsl", "/Users/Sarah/Desktop/Computer_Graphics/Assignment3A/Assignment3A/fshader36.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		NULL);

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		NULL);

	mvpi = glGetUniformLocation(program, "mvp");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void mymouse(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            isPressed = true;
            glfwGetCursorPos(window, &oldX, &oldY);
        }
        else if(GLFW_RELEASE)
        {
            isPressed = false;
            hrotate = 0;
            vrotate = 0;
        }
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos)
{
    if(isPressed) {
        hrotate += 0.01 * (xPos - oldX);
        vrotate += 0.01 * (yPos - oldY);
        
        gModel = glm::rotate(gModel, GLfloat(hrotate), glm::vec3(0.0, 1.0, 0.0));
        gModel = glm::rotate(gModel, GLfloat(vrotate), glm::vec3(1.0, 0.0, 0.0));
    }
}

void mykey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
        
        // zoom out
        // increase fov
        if(key == GLFW_KEY_UP) {
            fov += fovOffset;
        }
        // zoom in
        // decrease fov
        if(key == GLFW_KEY_DOWN) {
            fov -= fovOffset;
        }
        
        // aspect ratio
        if(key == GLFW_KEY_LEFT) {
            aspect += aspectDelta;
        }
        if(key == GLFW_KEY_RIGHT) {
            aspect -= aspectDelta;
        }
        
        // increase near clipping plane
        if(key == GLFW_KEY_COMMA) {
            ncp += ncpDelta;
            printf("NCP comma click value: %f\n", ncp);
        }
        // decrease far clipping plane
        if(key == GLFW_KEY_PERIOD) {
            ncp -= ncpDelta;
            printf("NCP period click value: %f\n", ncp);
        }
        // increase far clipping plane
        if(key == GLFW_KEY_K) {
            fcp += fcpDelta;
            printf("FCP K click value: %f\n", fcp);
        }
        //decrease far clipping plane
        if(key == GLFW_KEY_L) {
            fcp -= fcpDelta;
            printf("FCP L click value: %f\n", fcp);
        }
        
        // translate x axis
        if(key == GLFW_KEY_X) {
            gModel = glm::translate(gModel, glm::vec3(tranScale, 0.0f, 0.0f));
        }
        if(key == GLFW_KEY_C) {
            gModel = glm::translate(gModel, glm::vec3(-tranScale, 0.0f, 0.0f));
        }
        // translate y axis
        if(key == GLFW_KEY_Y) {
            gModel = glm::translate(gModel, glm::vec3(0.0f, tranScale, 0.0f));
        }
        if(key == GLFW_KEY_T) {
            gModel = glm::translate(gModel, glm::vec3(0.0f, -tranScale, 0.0f));
        }
        // translate z axis
        if(key == GLFW_KEY_Z) {
            gModel = glm::translate(gModel, glm::vec3(0.0f, 0.0f, tranScale));
        }
        if(key == GLFW_KEY_A) {
            gModel = glm::translate(gModel, glm::vec3(0.0f, 0.0f, -tranScale));
        }
        
        // rotate x axis
        if(key == GLFW_KEY_G) {
            gModel = glm::rotate(gModel, rotateValDelta , glm::vec3(1.0f, 0.0f, 0.0f));
        }
        // rotate y axis
        if(key == GLFW_KEY_H) {
            gModel = glm::rotate(gModel, rotateValDelta , glm::vec3(0.0f, 1.0f, 0.0f));
        }
        // rotate z axis
        if(key == GLFW_KEY_B) {
            gModel = glm::rotate(gModel, rotateValDelta , glm::vec3(0.0f, 0.0f, 1.0f));
        }
        
        // reverse rotate x axis
        if(key == GLFW_KEY_N) {
            gModel = glm::rotate(gModel, -rotateValDelta , glm::vec3(1.0f, 0.0f, 0.0f));
        }
        // reverse rotate y axis
        if(key == GLFW_KEY_M) {
            gModel = glm::rotate(gModel, -rotateValDelta , glm::vec3(0.0f, 1.0f, 0.0f));
        }
        // reverse rotate z axis
        if(key == GLFW_KEY_J) {
            gModel = glm::rotate(gModel, -rotateValDelta , glm::vec3(0.0f, 0.0f, 1.0f));
        }
        
        // reset values
        if(key == GLFW_KEY_R) {
            fov = fovValDefault;
            aspect = aspectValDefault;
            ncp = ncpValDefault;
            fcp = fcpValDefault;
            gModel = modelDefault;
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
	window = glfwCreateWindow(640, 640, "Assignment 3A", NULL, NULL);

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

	glfwSetKeyCallback(window, mykey);
	glfwSetMouseButtonCallback(window, mymouse);
    // set motion callback for current window
    glfwSetCursorPosCallback(window, cursor_pos_callback);


	do{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);     // clear the window

        glm::mat4 model = gModel;   // scale of the matrix
        glm::vec3 eye(0.0f, 0.0f, 2.0f);
        glm::vec3 at(0.0f, 0.0f, 0.0f);
        glm::vec3 up(0.0, 1.0f, 0.0f);
        view = glm::lookAt(eye, at, up);
        
        Projection = glm::perspective(glm::radians(fov), aspect, ncp, fcp);
		// compute mvp projection
        mvp = Projection * view * model;

		glUniformMatrix4fv(mvpi, 1, GL_FALSE, glm::value_ptr(mvp));

		glDrawArrays(GL_TRIANGLES, 0, NumVertices);    // draw the points
		/* update other events like input handling */
		glfwPollEvents();
		glfwSwapBuffers(window);
	} while (!glfwWindowShouldClose(window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;

}
