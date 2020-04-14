Sarah McLaughlin – skm9b3
14237628
CS 4610 – Computer Graphics I
31 March 2020
# Assignment 3A

## Part 1: Run Assignment3a.zip

### Included headers using quotations (lines 10 – 19):

#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/normal.hpp"

### Include direct folder access to shader files (line 98):
program = InitShader("/Users/Sarah/Desktop/Computer_Graphics/Assignment3A/Assignment3A/vshader36.glsl", "/Users/Sarah/Desktop/Computer_Graphics/Assignment3A/Assignment3A/fshader36.glsl");

Comment out apple if statements (lines 152 and 156)

 
## Part 2: Change field of view and aspect ratio of camera and change values near and far clipping plane


### Define default values (38 – 54):
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



Define projection in Main() (lines 348 – 350):
Projection = glm::perspective(glm::radians(fov), aspect, ncp, fcp);
// compute mvp projection
mvp = Projection * view * model;



### Change field of view and aspect ratio (lines 203 – 231):
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
 


## Part 3: Us ing your graphical user interface (GUI) such as GLFW or equivalent, together with the mouse and keyboard, interactively perform the following tasks


### Zoom in and out changing FOV (lines 197 – 206):
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
  

### Translate model/camera in X, Y, Z direction (lines 237 – 257):
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

  


### Rotate model/camera around X, Y, and Z axes (lines 259 – 283):
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

  


### Rotate mode/camera according to moving direction and distance of mouse (lines 162 – 188):
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

  

*** SEE VIDEO FOR CLEAR MOUSE ROTATION

