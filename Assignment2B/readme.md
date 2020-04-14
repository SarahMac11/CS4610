# Assignment 2B

## Part A: Integrate Assignment 1 Part B with Assignment 2a Part A, so that we can display the Sierpinski Gasket at the user's mouse positions.

I derived the initial DrawSquare.cpp from Assignment 2A by adding code from example1.cpp.
Predefined variables added to DrawSquare.cpp:
const int numOfGaskets = 8;
const int NumPoints = 5000;
GLfloat points[NumPoints * numOfGaskets * 2];
GLfloat gasketPoints[8];

I commented out the drawSquare function (lines 112 - 121).

### Created a drawGasket function (lines 77 – 108):
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
}

### Altered myMouse function (lines 136 – 142):
//		drawSquare(x, y);
        		drawGasket(x, y);
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
//		glGenVertexArrays(1, &vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);


## Part B: Implementing the Callback Function using Mouse and Keyboard

### Vshader – Included additional vPosition (lines 44 – 45):
gl_Position = rz * ry * rx * vPosition;
gl_Position = gl_Position + position;


Direct access to shader files:
	GLuint program = InitShader("/Users/Sarah/Desktop/Computer_Graphics/Assignment2B/PartB/vshader36.glsl", "/Users/Sarah/Desktop/Computer_Graphics/Assignment2B/PartB/fshader36.glsl");

### Define variables sent to vShader (lines 62 – 64):
GLuint  theta;  // The location of the "theta" shader uniform variable
GLuint positionInt;
GLuint cosineInt;

### Mymouse callback (lines 128 – 139):
if (action == GLFW_PRESS) {
       rotation = true;
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            Axis = Xaxis;
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            Axis = Yaxis;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            Axis = Zaxis;
        }
}


### Key callback press and release (lines 147 – 211):
if (action == GLFW_PRESS) {
        switch (key)
        {
            // start and stop
            case GLFW_KEY_S:
                rotation = !rotation;
                break;
                
            // escape
            case GLFW_KEY_Q:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            
            // x axis
            case GLFW_KEY_A:
                Key_Pressed[0] = key;
                break;
            case GLFW_KEY_D:
                Key_Pressed[1] = key;
                break;
                
            // y axis
            case GLFW_KEY_W:
                Key_Pressed[2] = key;
                break;
            case GLFW_KEY_X:
                Key_Pressed[3] = key;
                break;
                
            // z axis
            case GLFW_KEY_F:
                Key_Pressed[4] = key;
                break;
            case GLFW_KEY_B:
                Key_Pressed[5] = key;
                break;
        }
    }
    if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_A:
            Key_Pressed[0] = -1;
            break;
        case GLFW_KEY_D:
            Key_Pressed[1] = -1;
            break;
        case GLFW_KEY_W:
            Key_Pressed[2] = -1;
            break;
        case GLFW_KEY_X:
            Key_Pressed[3] = -1;
            break;
        case GLFW_KEY_F:
            Key_Pressed[4] = -1;
            break;
        case GLFW_KEY_B:
            Key_Pressed[5] = -1;
            break;
        }
    }


### Offset axis vectors (lines 213 – 233):
if (Key_Pressed[0] != -1)
        Dir_X = -offset;
    if (Key_Pressed[1] != -1)
        Dir_X = offset;
    
    if (Key_Pressed[2] != -1)
        Dir_Y = offset;
    if (Key_Pressed[3] != -1)
        Dir_Y = -offset;
    
    if (Key_Pressed[4] != -1)
        Dir_Z = offset;
    if (Key_Pressed[5] != -1)
        Dir_Z = -offset;
   
    if (Key_Pressed[0] == -1 && Key_Pressed[1] == -1)
        Dir_X = 0;
    if (Key_Pressed[2] == -1 && Key_Pressed[3] == -1)
        Dir_Y = 0;
    if (Key_Pressed[4] == -1 && Key_Pressed[5] == -1)
        Dir_Z = 0;


### Position sent to vshader and calculations (lines 287 – 298):

if(rotation)
            Theta[Axis] = (int)(Theta[Axis] + 1.0) % 360;

        position[0] += Dir_X;
        position[1] += Dir_Y;
        position[2] += Dir_Z;
        position[3] = 0;    // default position

        cosine[0] = cos(Theta[Xaxis] * pi / 180.0f);
        cosine[1] = cos(Theta[Yaxis] * pi / 180.0f);
        cosine[2] = cos(Theta[Zaxis] * pi / 180.0f);

        glUniform3fv(theta, 1, Theta);
        glUniform4fv(positionInt, 1, position);
        glUniform3fv(cosineInt, 1, cosine);

