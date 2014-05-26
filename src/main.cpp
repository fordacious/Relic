#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <time.h>
#include <stdlib.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// Light stuff
struct Light {
    double x = 0;
    double y = 0;
    double z = 0;

    double r = 0xff;
    double g = 0xff;
    double b = 0xff;

    double intensity = 0.1;
};

Light * selectedLight;

Light * lights        [10];
float lightPositions  [10*3];
float lightColours    [10*3];
float lightIntensities[10];
float lightFalloffs   [10*3];

int numLights = 3;

// Window stuff
double FPS = 60;
double millisecondsPerFrame = 1000/FPS;
double WIDTH = 800;
double HEIGHT = 600;

double t = 0;

// Shader stuff
GLuint shaderProgram;
GLuint pixelShader;

std::map<std::string, GLuint> shaders;

// Texture stuff
GLuint diffuseHandle = 0;
GLuint heightHandle  = 0;
GLuint normalHandle  = 0;
sf::Image diffuseMap;
sf::Image normalMap;
sf::Image heightMap;
bool generatedTextures = false;

GLuint compileShader(GLuint type, const GLchar *source, GLint sourceLen) {
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, &source, &sourceLen);
   glCompileShader(shader);
   GLint isCompiled;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

   if (!isCompiled) {
      GLint length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      std::string log(length, ' ');
      glGetShaderInfoLog(shader, length, &length, &log[0]);
      std::cout << log << std::endl;
      exit(0);
   }

   return shader;
}

// Loads and compiles a shader for you
// maps names to shaders too :D
void loadShader(std::string filename, std::string refname) {
   std::cout << "Loading " << (filename) << std::endl;

   std::ifstream ifs(filename.c_str());
   std::string content(
      (std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>())
   );

   GLint sourceLen = content.size();
   const char *source = content.c_str();

   shaders[refname] = compileShader(GL_FRAGMENT_SHADER, source, sourceLen);
   if (!shaders[refname]) {
      std::cout << "Error compiling " + filename << std::endl;
   } else {
      std::cout << "shader compiled successfully" << std::endl;
   }
}

void renderTest() {
    glLoadIdentity();

    glUseProgram(shaderProgram);

    // Set all the variables in the shader
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPositions"),   numLights * 3, lightPositions);//(light.x + 1) * 0.5, (light.y + 1) * 0.5, light.z);
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColours"),     numLights * 3, lightColours);//light.r / 0xff, light.g / 0xff, light.b / 0xff);
    glUniform1fv(glGetUniformLocation(shaderProgram, "lightIntensities"), numLights, lightIntensities);// light.intensity);
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightFalloffs"),    numLights * 3, lightFalloffs);//0,0,0.1);
    
    glUniform3f(glGetUniformLocation(shaderProgram, "ambient"), 0.2 / numLights,0.2 / numLights,0.2 / numLights);//0.7,0.7,0.7);
    glUniform1i(glGetUniformLocation (shaderProgram, "numLights"), numLights);

    glActiveTexture(GL_TEXTURE0 + diffuseHandle);
    glBindTexture(GL_TEXTURE_2D, diffuseHandle);
    glUniform1i(glGetUniformLocation(shaderProgram, "diffuseTexture"), diffuseHandle);

    glActiveTexture(GL_TEXTURE0 + heightHandle);
    glBindTexture(GL_TEXTURE_2D, heightHandle);
    glUniform1i(glGetUniformLocation(shaderProgram, "heightTexture"), heightHandle);

    glActiveTexture(GL_TEXTURE0 + normalHandle);
    glBindTexture(GL_TEXTURE_2D, normalHandle);
    glUniform1i(glGetUniformLocation(shaderProgram, "normalTexture"), normalHandle);

    glUniform2f(glGetUniformLocation(shaderProgram, "resolution"), 800, 600);

    // Draw the actual brick wall
    glBegin(GL_QUADS);
        glColor3d(0.5,0.5,0.5);

        glVertex3f(-0.5,-0.5,0);
        glVertex3f(0.5,-0.5,0);
        glVertex3f(0.5,0.5,0);
        glVertex3f(-0.5,0.5,0);
    glEnd();

    // Draw each light dot so you know where the lights are
    glUseProgram(0);
    int i = 0;
    for (i=0;i<numLights;i++) {
    	glBegin(GL_QUADS);
            glColor3d(0,0,0);

            glVertex3f(lights[i]->x-0.005 + 0.003,lights[i]->y-0.005 - 0.003,0);
            glVertex3f(lights[i]->x+0.005 + 0.003,lights[i]->y-0.005 - 0.003,0);
            glVertex3f(lights[i]->x+0.005 + 0.003,lights[i]->y+0.005 - 0.003,0);
            glVertex3f(lights[i]->x-0.005 + 0.003,lights[i]->y+0.005 - 0.003,0);
        glEnd();
        glBegin(GL_QUADS);
            glColor3d(lights[i]->r / 0xff, lights[i]->g / 0xff, lights[i]->b / 0xff);

            glVertex3f(lights[i]->x-0.005,lights[i]->y-0.005,0);
            glVertex3f(lights[i]->x+0.005,lights[i]->y-0.005,0);
            glVertex3f(lights[i]->x+0.005,lights[i]->y+0.005,0);
            glVertex3f(lights[i]->x-0.005,lights[i]->y+0.005,0);
        glEnd();
       
    }
}

void renderingThread(sf::Window* window)
{
    int i;
    // activate the window's context
    window->setActive(true);

    glMatrixMode(GL_MODELVIEW);

    // the rendering loop
    while (window->isOpen())
    {
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Construct light arrays
        int j = 0;
        for (i=0; i<numLights * 3; i+= 3) {
            //std::cout << lights[j]->x << std::endl;
            lightPositions[i + 0] = (lights[j]->x + 1) * 0.5;
            lightPositions[i + 1] = (lights[j]->y + 1) * 0.5;
            lightPositions[i + 2] = lights[j]->z;

            lightColours[i + 0]   = lights[j]->r;
            lightColours[i + 1]   = lights[j]->g;
            lightColours[i + 2]   = lights[j]->b;

            lightIntensities[j] = lights[j]->intensity;

            lightFalloffs[i + 0] = 1;
            lightFalloffs[i + 1] = 1;
            lightFalloffs[i + 2] = 1;
            j += 1;
        }

        // draw...
        renderTest();

        // end the current frame (internally swaps the front and back buffers)
        window->display();
    }
}

void glInit () {

	// Load the 3 texture files

    if (!diffuseMap.loadFromFile("../assets/textures/brick_768_768/brick_768_768_diffuse.png")) {
        std::cout << "failed to load texture" << std::endl;
        return;
    }
    if (!heightMap.loadFromFile("../assets/textures/brick_768_768/brick_768_768_height.png")) {
        std::cout << "failed to load texture" << std::endl;
        return;
    }
    if (!normalMap.loadFromFile("../assets/textures/brick_768_768/brick_768_768_normal.png")) {
        std::cout << "failed to load texture" << std::endl;
        return;
    }

    std::cout << "loaded texture" << std::endl;

    // Load and bind the textures on the graphics card

    glViewport(0, 0, WIDTH, HEIGHT);
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1000);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glGenTextures(1, &diffuseHandle);
    glBindTexture(GL_TEXTURE_2D, diffuseHandle);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        diffuseMap.getSize().x, diffuseMap.getSize().y,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, diffuseMap.getPixelsPtr()
    );

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glGenTextures(1, &heightHandle);
    glBindTexture(GL_TEXTURE_2D, heightHandle);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        heightMap.getSize().x, heightMap.getSize().y,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, heightMap.getPixelsPtr()
    );

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glGenTextures(1, &normalHandle);
    glBindTexture(GL_TEXTURE_2D, normalHandle);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        normalMap.getSize().x, normalMap.getSize().y,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, normalMap.getPixelsPtr()
    );

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // Load the lighting shader

    loadShader("../assets/shaders/lightingtest.frag", "lightingtest");

    shaderProgram = glCreateProgram();
    pixelShader = shaders["lightingtest"];

    glAttachShader(shaderProgram, pixelShader);
    glLinkProgram(shaderProgram);

}

int main (int argc, char ** argv) {

    std::cout << "Relic C++ Version" << std::endl;

    sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "Relic", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    // load resources, initialize the OpenGL states, ...
    glInit();

    // Start teh rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    sf::Clock clock;

    srand(time(NULL));

    int i;
    Light * light;
    for (i=0;i<numLights;i++) {
        light = new Light();
        lights[i] = light;
	}

    i = 0;
    selectedLight = lights[i];

    // run the main loop
    while (true)
    {
        double elapsedTime = clock.restart().asMilliseconds();
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                break;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
                WIDTH = event.size.width;
                HEIGHT = event.size.height;
            } else if (event.type == sf::Event::MouseButtonReleased) {
                i += 1;
                selectedLight = lights[i % numLights];
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == 0) { // A pressed - [intensity intensifies]
                    selectedLight->intensity *= 1.2;
                }  else if (event.key.code == 3) { // D pressed - decrease intensity
                    selectedLight->intensity *= 0.8;
                }  else if (event.key.code == 4) { // E - randomises light colour
                	selectedLight->r = rand() % 0xFF;
	                selectedLight->g = rand() % 0xFF;
	                selectedLight->b = rand() % 0xFF;
                } else if (event.key.code == 36) { // ESC - closes program
                    exit(0);
                }
            }
        }
 
        t += 1;

        selectedLight->x += (sf::Mouse::getPosition(window).x / (double)WIDTH  - 0.5);
        selectedLight->y -= (sf::Mouse::getPosition(window).y / (double)HEIGHT - 0.5);
        sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);

        elapsedTime = clock.restart().asMilliseconds();

        sf::sleep(sf::milliseconds(millisecondsPerFrame - elapsedTime));
    }

    std::cout << "Bai!!!" << std::endl;

    return 0;
}