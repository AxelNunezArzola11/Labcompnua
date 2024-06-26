#pragma once

#include "CommonValues.h"
#include <vector>
#include <string>
/* pa windows
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>*/
///pa linux
#include <GL/glew.h>
#include<glm/glm.hpp>
#include <GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader_light.h"
class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		
	~Skybox();
private:
	Mesh* skyMesh;
	Shader* skyShader;
	GLuint textureId;
	GLuint uniformProjection, uniformView;

};

