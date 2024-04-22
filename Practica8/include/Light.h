#pragma once
/* para windows
#include <glew.h>
#include <glm.hpp>*/
//para linux
#include <GL/glew.h>
#include<glm/glm.hpp>
//#include <GLFW/glfw3.h>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

