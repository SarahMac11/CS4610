// DrawSquare.cpp     
// Generate a square on a solid background at user’s mouse position


#include "GL/glew.h"
#include <stdio.h>
#include <stdlib.h>
#include "GLFW/glfw3.h"

GLuint shader_programme;
GLuint vao;
int w = 640;;
int h = 640;
int i = 0;

const int numOfGaskets = 8;

GLfloat size = 70;
int cnt = 3;
GLuint buffer;
const int NumPoints = 5000;
GLfloat points[NumPoints * numOfGaskets * 2];
GLfloat gasketPoints[8];


//----------------------------------------------------------------------------
void init( void )
{
    
	GLuint vert_shader, frag_shader;
	/* GL shader programme object [combined, to link] */

    // Create and initialize a buffer object
    
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

	// Create a vertex array object

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// "attribute #0 is created from every 2 variables in the above buffer, of type
	// float (i.e. make me vec2s)"
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // Load shaders and use the resulting shader program
	const char *vertex_shader = "#version 410\n"
		"in vec4 vPosition;"
		"void main () {"
		"	gl_Position = vPosition;"
		"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char *fragment_shader = "#version 410\n"
		"out vec4 FragColor;"
		"void main () {"
		"	FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );"
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

void drawGasket(int x, int y)
{
    // 8 points taken from drawSquare function
    gasketPoints[0] = (2.0f * (x + size) / w )- 1.0f;
    gasketPoints[1] = 1.0f - (2.0f * y) / w;
    gasketPoints[2] = (2.0f * (x - size) / w) - 1.0f;
    gasketPoints[3] = 1.0f - (2.0f * y) / w;
    gasketPoints[4] = (2.0f * x / w) - 1.0f;
    gasketPoints[5] = 1.0f - (2.0f * (y - size - 20)) / w;
    gasketPoints[6] = (2.0f * x / w) - 1.0f;   // include offset
    gasketPoints[7] = 1.0f - (2.0f * y) / w;   // include offset
    
    // Specifiy the vertices for a triangle
    // use gasket points created
    GLfloat vertices[] = { gasketPoints[0], gasketPoints[1],  gasketPoints[2], gasketPoints[3],  gasketPoints[4], gasketPoints[5] };
    
    int holdPlace = i + NumPoints*2;
    points[i] = gasketPoints[6];
    points[1 + i] = gasketPoints[7];
    for (i = 2 + i; i < holdPlace; i+=2) {  // hold place updates the points as the for loop goes through
        int j = rand()%3;   // pick a vertex at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = (points[i - 2] + vertices[2*j]) / 2.0;
        points[i+1] = (points[i - 1] + vertices[2 * j+1]) / 2.0;
    }
    
    cnt += NumPoints;   // # of points
    
    printf("i %d and count %d", i, cnt);
}

//void drawSquare(int x, int y)
//{
//	y = w - y; /* invert y position */
//	points[i] = (2.0f * (x+size) / w )- 1.0f;
//	points[i + 1] = 1.0f - (2.0f * (y+size)) / w;;
//	points[i + 2] = (2.0f * (x - size) / w) - 1.0f;
//	points[i + 3] = 1.0f - (2.0f * (y + size)) / w;;
//	points[i + 4] = (2.0f * (x + size) / w) - 1.0f;
//	points[i + 5] = 1.0f - (2.0f * (y - size)) / w;;
//	points[i + 6] = (2.0f * (x - size) / w) - 1.0f;
//	points[i + 7] = 1.0f - (2.0f * (y + size)) / w;;
//	points[i + 8] = (2.0f * (x + size) / w) - 1.0f;
//	points[i + 9] = 1.0f - (2.0f * (y - size)) / w;;
//	points[i + 10] = (2.0f * (x - size) / w) - 1.0f;
//	points[i + 11] = 1.0f - (2.0f * (y - size)) / w;
//	i += 12;
//	cnt+=6;
//}


void mymouse(GLFWwindow* window, int button, int action, int mods){
	if (GLFW_PRESS == action) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
//		drawSquare(x, y);
        drawGasket(x, y);
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//		glGenVertexArrays(1, &vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

		// "attribute #0 is created from every 2 variables in the above buffer, of type
		// float (i.e. make me vec2s)"
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
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

	glfwSetMouseButtonCallback(window, mymouse);

   do{
	   glClear(GL_COLOR_BUFFER_BIT);     // clear the window
	   glUseProgram(shader_programme);
	   glBindVertexArray(vao);
	   glDrawArrays(GL_POINTS, 0, cnt );    // draw the points
	   /* update other events like input handling */
	   glfwPollEvents();
	   glfwSwapBuffers(window);
   }
   while (!glfwWindowShouldClose(window));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
	return 0;

}
