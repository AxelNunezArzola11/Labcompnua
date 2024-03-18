/*
Pr�ctica 5: Optimizaci�n y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
/*
#include <glew.h>
#include <glfw3.h>
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/*
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
*/
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model Goddard_M;
///tuto roque
Model Goodddard_sin_cola;
Skybox skybox;
//ejercicio
///base

Model Goodard_base;

///Cabeza
Model Goodard_cabeza;
///Mandibula
Model Goddard_mandibula;
///Pierna Trasera
Model Goddard_Pata_Trasera;
////Pierna Delantera
Model Goddard_Pata_Delantera;

//Sphere cabeza = Sphere(0.5, 20, 20);

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	Goddard_M = Model();
	Goddard_M.LoadModel("Models/goddard_base.obj");
	Goodddard_sin_cola=Model();
	Goodddard_sin_cola.LoadModel("Models/goddardbase_tuto_roque.obj");
	Goodard_base= Model();
	Goodard_base.LoadModel("Models/ejerciciogoddardBase.obj");
	//cabeza
	Goodard_cabeza= Model();
	Goodard_cabeza.LoadModel("Models/ejerciciogoddardCabeza.obj");
	///mandibula
	 Goddard_mandibula=Model();
	 Goddard_mandibula.LoadModel("Models/ejerciciogoddardmandibula.obj");
	 /// Pata trasera
	 Goddard_Pata_Trasera=Model();
	 Goddard_Pata_Trasera.LoadModel("Models/ejerciciogoddardPataTraesera.obj");
	 ///Pata delantera
	 Goddard_Pata_Delantera=Model();
	Goddard_Pata_Delantera.LoadModel("Models/ejerciciogoddardPataDelantera.obj");




	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelaux2(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		//------------*INICIA DIBUJO DE NUESTROS DEM�S OBJETOS-------------------*
		//Goddard
		///color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		modelaux = model;
		modelaux2= model;
		color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goodard_base.RenderModel();

		//Goddard_M.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		//color = glm::vec3(0.0f, 0.0f, 1.0f);
		//En sesi�n se separara una parte del modelo de Goddard y se unir� por jeraqu�a al cuerpo
		//modelaux = model;
		//cabeza
		model=modelaux;
		model = glm::translate(model, glm::vec3(0.1f, 3.5f, 0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulocabeza()), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux=model;
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goodard_cabeza.RenderModel();
		//mandibula
		model=modelaux;
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -0.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulomandibula()), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_mandibula.RenderModel();
		///pata trazera derecha
		model=modelaux2;
		model = glm::translate(model, glm::vec3(-1.0f, 0.5f, 0.0f));
		modelaux=modelaux2;
		model = glm::rotate(model, glm::radians(mainWindow.getangulopata_trasera_der()), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 0.0f); // Color amarillo
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Pata_Trasera.RenderModel();
//////////////segunda pata trazera izquierda
		model=modelaux;
		model = glm::translate(model, glm::vec3(-1.0f, 0.5f, 1.0f));
		//color = glm::vec3(1.0f, 1.0f, 0.0f); // Color amarillo
		modelaux=model;
		model = glm::rotate(model, glm::radians(mainWindow.getangulopata_trasera_izq()), glm::vec3(0.0f, 0.0f, 1.0f));

		color = glm::vec3(0.5f, 0.25f, 0.0f); // Color café

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Pata_Trasera.RenderModel();
///primera pata delantera izq
		model=modelaux2;
		model = glm::translate(model, glm::vec3(1.0f, 0.5f, 1.0f));
		modelaux2=model;
		model = glm::rotate(model, glm::radians(mainWindow.getangulopata_delantera_izq()), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(0.5f, 0.0f, 0.5f); // Color violeta
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Pata_Delantera.RenderModel();
///seguna pata delnatera der
		model=modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		modelaux2=model;
		model = glm::rotate(model, glm::radians(mainWindow.getangulopata_delantera_der()), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(1.0f, 0.5f, 0.5f); // Color rosa
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Goddard_Pata_Delantera.RenderModel();













		//Siguientes modelos
		/* Ejercicio:
		1.- Separar las 4 patas de Goddard del modelo del cuerpo, unir por medio de jerarqu�a cada pata al cuerpo de Goddard
		2.- Hacer que al presionar una tecla cada pata pueda rotar un m�ximo de 45� "hacia adelante y hacia atr�s"
		*/

		//pata delantera derecha
		modelaux = model;

		// pata delantera izquierda
		modelaux = model;
		//pata trasera derecha
		modelaux = model;

		//pata trasera izquierda
		modelaux = model;


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
