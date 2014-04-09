#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <time.h>
#include <stdlib.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

typedef char byte;

struct Light {
	double x = 0;
	double y = 0;
	double z = 0;

	double r = 0xff;
	double g = 0xff;
	double b = 0xff;

	double intensity = 1;
};

Light light;
std::map<std::string, GLuint> shaders;

double FPS = 60;
double millisecondsPerFrame = 1000/FPS;
double WIDTH = 800;
double HEIGHT = 600;

double t = 0;

GLuint shaderProgram;
GLuint pixelShader;

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

void loadShader(std::string filename, std::string refname) {
   std::cout << "Loading " << (filename) << std::endl;

   std::ifstream ifs(filename);
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
	glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), (light.x + 1) * 0.5, (light.y + 1) * 0.5, light.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "lightCol"), light.r / 0xff, light.g / 0xff, light.b / 0xff);
	glUniform1f(glGetUniformLocation(shaderProgram, "lightIntensity"), light.intensity);

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

	glUniform3f(glGetUniformLocation(shaderProgram, "ambient"), 0.7,0.7,0.7);
	glUniform3f(glGetUniformLocation(shaderProgram, "falloff"), 0,0,0.1);

	//std::cout << light.x << " " << light.y << std::endl;

	glBegin(GL_QUADS);
		glColor3d(0.5,0.5,0.5);

		glVertex3f(-0.5,-0.5,0);
		glVertex3f(0.5,-0.5,0);
		glVertex3f(0.5,0.5,0);
		glVertex3f(-0.5,0.5,0);
	glEnd();

	glUseProgram(0);
    glBegin(GL_QUADS);
		glColor3d(light.r / 0xff, light.g / 0xff, light.b / 0xff);

		glVertex3f(light.x-0.005,light.y-0.005,0);
		glVertex3f(light.x+0.005,light.y-0.005,0);
		glVertex3f(light.x+0.005,light.y+0.005,0);
		glVertex3f(light.x-0.005,light.y+0.005,0);
    glEnd();
}

void renderingThread(sf::Window* window)
{
    // activate the window's context
    window->setActive(true);

    glMatrixMode(GL_MODELVIEW);

    // the rendering loop
    while (window->isOpen())
    {
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        renderTest();

        // end the current frame (internally swaps the front and back buffers)
        window->display();
    }
}

void glInit () {

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

    // load resources, initialize the OpenGL states, ...
	glInit();

    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    sf::Clock clock;

    srand(time(NULL));

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
	        	light.r = rand() % 0xFF;
	        	light.g = rand() % 0xFF;
	        	light.b = rand() % 0xFF;
            } else if (event.type == sf::Event::KeyPressed) {
            	if (event.key.code == 0) {
            		light.intensity *= 1.2;
            	}  else if (event.key.code == 3) {
					light.intensity *= 0.8;
            	} else if (event.key.code == 36) {
            		exit(0);
            	}
            	//std::cout << event.key.code << std::endl;
            }
        }
 
        t += 1;

        light.x += (sf::Mouse::getPosition(window).x / (double)WIDTH  - 0.5);
        light.y -= (sf::Mouse::getPosition(window).y / (double)HEIGHT - 0.5);
        sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);

        elapsedTime = clock.restart().asMilliseconds();

    	sf::sleep(sf::milliseconds(millisecondsPerFrame - elapsedTime));
    }

    return 0;
}