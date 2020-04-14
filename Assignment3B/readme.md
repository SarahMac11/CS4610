# Assignment 3B

## Part A:  Obj Parser
Included “pig.obj”: Product > Scheme > Edit Scheme > Run > Options: Use custom working directory (Assignment3B folder selected).

## Part B: Illumination and Shading
Support for light source:
Predefined ambient, diffuse and specular light and material properties and define light position and shininess (lines 53 – 65):
// Vertices of a unit cube centered at origin, sides aligned with axes
GLuint Shininess, LightID, AmbientProduct, DiffuseProduct, SpecularProduct, LightPosition;
// default light properties
glm::vec4 light_position(0.0, 0.0, 4.0, 0.0); // x y z w
glm::vec4 light_ambient(0.2, 0.2, 0.2, 1.0); // R G B A
glm::vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
glm::vec4 light_specular(1.0, 1.0, 1.0, 1.0);
// default material properties
glm::vec4 material_ambient(1.0, 0.0, 1.0, 1.0);
glm::vec4 material_diffuse(1.0, 0.8, 0.0, 1.0);
glm::vec4 material_specular(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

### Interactively turn light(s) on and off:
Using mymouse callback to turn lights on and off (lines 176 – 213):
if (action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT) {
            isPressed = !isPressed;     // opposite bool is set each click
            if (isPressed == true)
            {
                // set default light properties
                light_position = glm::vec4(0.0, 0.0, 4.0, 0.0); // x y z w
                light_ambient = glm::vec4(0.2, 0.2, 0.2, 1.0); // R G B A
                light_diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
                light_specular = glm::vec4(1.0, 1.0, 1.0, 1.0);
                // set default material properties
                material_ambient = glm::vec4(1.0, 0.0, 1.0, 1.0);
                material_diffuse = glm::vec4(1.0, 0.8, 0.0, 1.0);
                material_specular = glm::vec4(1.0, 0.8, 0.0, 1.0);
                material_shininess = 100.0;
            }
            else {
                // lights off = 0
                // default light properties
                light_position = glm::vec4(0.0, 0.0, 0.0, 0.0); // x y z w
                light_ambient = glm::vec4(0.0, 0.0, 0.0, 0.0); // R G B A
                light_diffuse = glm::vec4(0.0, 0.0, 0.0, 0.0);
                light_specular = glm::vec4(0.0, 0.0, 0.0, 0.0);
                // default material properties
                material_ambient = glm::vec4(0.0, 0.0, 0.0, 0.0);
                material_diffuse = glm::vec4(0.0, 0.0, 0.0, 0.0);
                material_specular = glm::vec4(0.0, 0.0, 0.0, 0.0);
                material_shininess = 0.0;
            }
        }
    }
 
 

### Support flat, Gouraud or Phong shading models:
Calculate vertex normal in test_vs.glsl (lines 17 – 38):
// Transform vertex  position into eye coordinates
    vec3 pos = (ModelView * vec4(vPosition, 1.0)).xyz;
    vec3 L = normalize((ModelView*LightPosition).xyz - pos);    //unit vector in direction of light source
    vec3 E = normalize(-pos);   // normalized vector in the direction of the viewer
    vec3 H = normalize(L + E);  // halfway vector
    // Transform vertex normal into eye coordinates
    vec3 N = normalize(ModelView*vec4(vNormal, 0.0)).xyz;
    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;
    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;
    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 1.0);
    color = ambient + diffuse + specular;
    color.a = 1.0;


### Change RGB values associated with ambient, diffuse and specular light and material properties:
Using mykey callback function to make these changes depending on keys (lines 221 – 266):
if (key == GLFW_KEY_A) {
            light_ambient = glm::vec4(0.0, 0.3, 1.0, 1.0);
            light_diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
            light_specular = glm::vec4 (1.0, 0.0, 0, 0.0);
        }
        if (key == GLFW_KEY_S) {
            light_ambient = glm::vec4 (0.2, 0.2, 0.2, 1.0);
            light_diffuse = glm::vec4 (1.0, 1.0, 1.0, 1.0);
            light_specular = glm::vec4 (1.0, 1.0, 1.0, 1.0);
        }
        if (key == GLFW_KEY_D) {
            light_ambient = glm::vec4(0.2, 0.2, 0.2, 1.0);
            light_diffuse = glm::vec4(0, 0, 0, 1.0);
            light_specular = glm::vec4(0, 0, 0, 1.0);
        }
        if (key == GLFW_KEY_F) {
            light_ambient = glm::vec4(0, 0, 0, 1.0);
            light_diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
            light_specular = glm::vec4(0, 0, 0, 1.0);
        }
        if (key == GLFW_KEY_G) {
            light_ambient = glm::vec4(0, 0, 0, 1.0);
            light_diffuse = glm::vec4(0, 0, 0, 1.0);
            light_specular = glm::vec4(1.0, 1.0, 1.0, 1.0);
        }
        if (key == GLFW_KEY_Z) {
            material_ambient = glm::vec4(1.0, 0.0, 1.0, 1.0);
            material_diffuse = glm::vec4 (0, 0, 0, 1.0);
            material_specular = glm::vec4 (0, 0, 0, 1.0);
        }
        if (key == GLFW_KEY_X) {
            material_ambient = glm::vec4(0, 0.0, 0, 1.0);
            material_diffuse = glm::vec4(1.0, 0.8, 0, 1.0);
            material_specular = glm::vec4(0, 0, 0, 1.0);
        }
        if (key == GLFW_KEY_C) {
            material_ambient = glm::vec4(0, 0, 0, 1.0);
            material_diffuse = glm::vec4(0, 0, 0, 1.0);
            material_specular = glm::vec4(1.0, 0.8, 0.0, 1.0);
        }
        if (key == GLFW_KEY_V) {
            material_ambient = glm::vec4(1.0, 0.0, 1.0, 1.0);
            material_diffuse = glm::vec4(1.0, 0.8, 0.0, 1.0);
            material_specular = glm::vec4(1.0, 0.8, 0.0, 1.0);
        }

## Part C: Texture Mapping (using RotateCube.cpp from Assignment3A)
Included “checker_256x256.jpg”: Product > Scheme > Edit Scheme > Run > Options: Use custom working directory (PartC folder selected).

### Include stb_image.h file and cube.obj (lines 16 – 17):

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

### Read texture image (lines 136 – 142):
    int x, y, n;
    int force_channels=4;
    unsigned char* image_data = stbi_load("/Users/Sarah/Desktop/Computer_Graphics/Assignment3B/PartC/checker_256x256.jpg", &x, &y, &n, force_channels);    if (!image_data) {
        fprintf( stderr, "ERROR: could not load texture file.");
    }

### Specify texture parameters (lines 144 – 155):
    GLuint texName;
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

### Modify quad function (lines 105 – 119):
void quad(int a, int b, int c, int d)
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vTexCoords[Index] = glm::vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vTexCoords[Index] = glm::vec2(1.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vTexCoords[Index] = glm::vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vTexCoords[Index] = glm::vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vTexCoords[Index] = glm::vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vTexCoords[Index] = glm::vec2(0.0, 1.0); Index++;
}

### Generate VAO and VBO (lilnes 157 – 182):
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * 4 * sizeof(GLfloat), points, GL_STATIC_DRAW);
    GLuint texcoords_vbo;
    glGenBuffers(1, &texcoords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texcoords_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36 * 2 * sizeof(GLfloat), vTexCoords, GL_STATIC_DRAW);
    GLuint texture_vao;
    glGenVertexArrays(1, &texture_vao);
    glBindVertexArray(texture_vao);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, texcoords_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

### Apply texture in vertex shader (vshader36.glsl):
#version 410
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
// Output data ; will be interpolated for each fragment.
out vec2 UV;
// Values that stay constant for the whole mesh.
uniform mat4 mvp;
void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  mvp * vec4(vertexPosition_modelspace,1);
    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}

### Apply texture in fragment shader (fshader36.glsl):
#version 410
in vec2 UV;
// Ouput data
out vec3 color;
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
void main(){
    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV ).rgb;
}

