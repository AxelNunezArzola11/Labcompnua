/*
Pr�ctica 7: Iluminaci�n 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
/* pa windows
#include <glew.h>
#include <glfw3.h>*/
///pa linux
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* pa windows
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
*/
//pa linux
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture Dado_Texture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
///EJRCICIO06
Model JEEP_cuerpo;
Model COFREFI;
Model llanta_1;
Model llanta_2;
/// practica07
Model lampara;
////paractica08
Model puerta;
Model gema;
Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];

///PARAC08
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];
SpotLight spotLights3[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


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

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


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

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}
void CrearDado()
{
///dado
unsigned int cub_indices[] = {
		/*0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2*/
		0, 1, 2,
		3, 4, 5,

		// back
		6, 7, 8,
		9, 10, 11,

		// left
		12, 13, 14,
		15, 16 ,17,

		// bottom
		18, 19, 20,
		21, 22, 23,

		// top
		24, 25, 26,
		27, 28, 29,

	};

	GLfloat cub_vertices[] = {
		//7
		//x		y		z				S		T			NX		NY		NZ
		0.0f, 0.0f, 0.0f,				0.0f,	0.5f,		0.0f,	0.0f,	-1.0f,	//0
		3.0f, 0.0f, 0.0f,				0.2f,	0.5f,		0.0f,	-1.0f,	-1.0f, 	//1
		1.5f, 2.064572880f, 3.0f,		0.0f,	0.0f,		0.0f,	0.0f,	-1.0f,	//2

		0.0f, 0.0f, 0.0f,				0.2f,	0.5f,		0.0f,	0.0f,	-1.0f,	//3
		3.0f, 0.0f, 0.0f,				0.4f,	0.5f,		0.0f,	-1.0f,	-1.0f, 	//4
		1.5f, 2.064572880f, -3.0f,		0.2f,	0.0f,		0.0f,	0.0f,	-1.0f,	//5

		3.0f, 0.0f, 0.0f,				0.4f,   0.5f,		0.0f,	0.0f,	1.0f,	//6
		3.9270509f, 2.8531695f, 0.0f,	0.6f,	0.5f,		0.0f,	0.0f,	1.0f,	//7
		1.5f, 2.064572880f, 3.0f,		0.4f,	0.00f,		0.0f,	0.0f,	1.0f,	//8

		3.0f, 0.0f, 0.0f,				0.6f,   0.5f,		0.0f,	0.0f,	1.0f,	//9
		3.9270509f, 2.8531695f, 0.0f,	0.8f,	0.5f,		0.0f,	0.0f,	1.0f,	//10
		1.5f, 2.064572880f, -3.0f,		0.6f,	0.0f,		0.0f,	0.0f,	1.0f,	//11
		
		3.9270509f, 2.8531695f, 0.0f,	0.8f, 0.5f,			-1.0f,	-1.0f,	-1.0f,	//12
		1.5f, 4.6165253057f, 0.0f,		1.0f,	0.5f,		-1.0f,	-1.0f,	-1.0f,	//13
		1.5f, 2.064572880f, 3.0f,		0.8f,	0.0f,		-1.0f,	-1.0f,	-1.0f,	//14

		3.9270509f, 2.8531695f, 0.0f,	0.2f, 1.0f,		-1.0f,	-1.0f,	1.0f,	//15
		1.5f, 4.6165253057f, 0.0f,		0.4f,	1.0f,		-1.0f,	-1.0f,	1.0f,	//16
		1.5f, 2.064572880f, -3.0f,		0.2f,	0.5f,		-1.0f,	-1.0f,	1.0f,	//17

		1.5f, 4.6165253057f, 0.0f,			0.0f, 1.0f,		1.0f,	-1.0f,	-1.0f,	//18
		-0.92705098f, 2.853169f, 0.0f,		0.2f,	1.0f,		1.0f,	-1.0f,	-1.0f,	//19
		1.5f, 2.064572880f, 3.0f,			0.0f,	0.5,		1.0f,	-1.0f,	-1.0f,	//20

		1.5f, 4.6165253057f, 0.0f,			0.4f, 1.0f,		1.0f,	-1.0f,	1.0f,	//21
		-0.92705098f, 2.853169f, 0.0f,		0.6f,	1.0f,		1.0f,	-1.0f,	1.0f,	//22
		1.5f, 2.064572880f, -3.0f,			0.4f,	0.5f,		1.0f,	-1.0f,	1.0f,	//23
		//x		y		z					S		T
		-0.92705098f, 2.853169f, 0.0f,		0.6f, 1.0f,		1.0f,	1.0f,	-1.0f,	//24
		0.0f, 0.0f, 0.0f,					0.8f,	1.0f,		1.0f,	1.0f,	-1.0f,	//25
		1.5f, 2.064572880f, 3.0f,			0.6f,	0.5f,		1.0f,	1.0f,	-1.0f,	//26
		 //x		y		z				S		T
		-0.92705098f, 2.853169f, 0.0f,		0.8f, 1.0f,		1.0f,	1.0f,	1.0f,	//27
		0.0f, 0.0f, 0.0f,					1.0f,	1.0f,		1.0f,	1.0f,	1.0f,	//28
		1.5f, 2.064572880f, -3.0f,			0.8f,	0.5f,		1.0f,	1.0f,	1.0f,	//29







	};
	Mesh* dado = new Mesh();
dado->CreateMesh(cub_vertices,cub_indices,240,36);
	////dado->CreateMesh(cub_vertices,cub_indices,232,29);
	meshList.push_back(dado);

}
int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	Dado_Texture=Texture("Textures/dad010caras.tga");
	Dado_Texture.LoadTextureA();





	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	///EJERCICI07
	JEEP_cuerpo=Model();
JEEP_cuerpo.LoadModel("Models/carrocuerpo.obj");

COFREFI=Model();
COFREFI.LoadModel("Models/COFREFI.obj");
llanta_1=Model();
llanta_1.LoadModel("Models/llantaTEXTU.obj");
llanta_2=Model();
llanta_2.LoadModel("Models/llantaTEXTU2.obj");
///practica 07
lampara=Model();
lampara.LoadModel("Models/lamp.obj");
////paractica 08
puerta=Model();
puerta.LoadModel("Models/puerta.obj");

gema=Model();
gema.LoadModel("Models/gema.obj");



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	//unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	/*
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	*/

	unsigned int spotLightCount = 0;
	unsigned int spotLightCount2 = 4;
	
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;
	


	//luz fija para puerta
	
	spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,
		0.0f, 2.0f,
		-8.0f, 8.0f, 3.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		///1.0f,0.0f,0.0f
		30.0f);
		///15.0f
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 


	///luz del faro del caro tiene que ser 2 
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f, ////color 
		1.0f, 2.0f, ///intensidad
		4.0f, 2.0f, -2.5f, ///posicion
		///4.0f, 2.0f, -3.0f,
		0.0f, 0.0f, 5.0f, ////direccion
		0.1f, 0.1f, 0.0f, ///  coeficientes
		///0.1f, 0.1f, 0.0f
		15.0f); ///angulo
	spotLightCount++;
	///luz helicoptero
	spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f, ////color 
		1.0f, 2.0f, ///intensidad
		10.0f, 2.0f, -2.5f, ///posicion
		///4.0f, 2.0f, -2.5f,
		0.0f, -5.0f, 0.0f, ////direccion
		1.0f, 0.0f, 0.0f, ///  coeficientes
		///0.1f, 0.1f, 0.0f
		15.0f); ///angulo
	spotLightCount++;

	/////arrreglo segundo luz
	spotLights2[0]=spotLights[0];
	spotLights2[1]=spotLights[1];
	spotLights2[2]=SpotLight(0.0f, 0.0f, 1.0f, ////color 
		1.0f, 2.0f, ///intensidad
		4.0f, 2.0f, -2.5f, ///posicion
		///4.0f, 2.0f, -3.0f,
		0.0f, 0.0f, -5.0f, ////direccion
		0.1f, 0.1f, 0.0f, ///  coeficientes
		///0.1f, 0.1f, 0.0f
		15.0f); ///angulo
	spotLights2[3]=spotLights[3];



	///lampara
		unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.001f,
		///0.5f, 1.0f
		0.0f, 1.0f, 0.0f,
		///0.0f 0.0f,0.0f en y
		///0.0f,-1.5f,0.0f
		///0.0f, -1.0f, 0.0f,
		0.1f, 0.1f, 0.1f
		///0.3f, 0.2f, 0.1f,
		);
	pointLightCount++;
	///segundo arreglo gema

	unsigned int pointLightCount2 = 0;

	pointLights2[0] = PointLight(0.0f, 0.0f, 1.0f,
		0.5f, 0.001f,
		///0.5f, 1.0f
		-5.0f, 1.0f, 15.0f,
		///0.0f 0.0f,0.0f en y
		///0.0f,-1.5f,0.0f
		///0.0f, -1.0f, 0.0f,
		0.1f, 0.1f, 0.1f
		///0.3f, 0.2f, 0.1f,
		);
	pointLightCount2++;



	

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
		int contador = 0;
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
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		////segundo arreglo
		spotLights2[0].SetFlash(lowerLight, camera.getCameraDirection());


		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		
		///shaderList[0].SetSpotLights(spotLights, spotLightCount);
		
		if (mainWindow.getlampgema() == 0.0f) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else if (mainWindow.getlampgema() == 1.0f) {
			shaderList[0].SetPointLights(pointLights2, pointLightCount2);
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
			glm::mat4 modelaux2(1.0);

		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();
		//Ejercicio 1: 
		
				model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado_Texture.UseTexture();
		meshList[3]->RenderMesh();
		
/*
		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		*/
	///ejercicio 07 carrito
	///cuerpo

	model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(4.0f, 0.5f, -1.5f));
		///0.0f,0.5f,-1.5f

		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getdesplazamiento()));
		////la luz del faro se mueva junto al coche y se apague
		if(mainWindow.getfarosd()==true){
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
			spotLights[2].SetPos(glm::vec3(4.0f, 1.2f,mainWindow.getdesplazamiento()));
		}
		else if(mainWindow.getfarosd()==false){
			shaderList[0].SetSpotLights(spotLights2, spotLightCount2);
			spotLights2[2].SetPos(glm::vec3(4.0f, 1.2f,(mainWindow.getdesplazamiento())));
		}
		
	
	


		//spotLights[2].SetPos(glm::vec3(4.0f, 1.2f,mainWindow.getdesplazamiento()));

		modelaux = model;
		modelaux2=model;
	//color = glm::vec3(0.5f, 0.5f, 0.5f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JEEP_cuerpo.RenderModel();

	//lanta trasera
	model=modelaux;
	model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -2.0f));

		modelaux = model;

		///modelaux2= model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_1.RenderModel();
		
///lanta trasera izquierda es la que se tiene que rotar
		 model=modelaux;
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_2.RenderModel();

///llanta delantera
model=modelaux;
model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_1.RenderModel();
		
///SEGUNDA LLANTA DELBATERA

model=modelaux;
model = glm::translate(model, glm::vec3(2.0f, 0.0f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_2.RenderModel();
		
	
	//cofre
	//model=modelaux2;
model=modelaux2;
//model = glm::translate(model, glm::vec3(0.0f, 0.8f, -1.0f));
model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		COFREFI.RenderModel();

	////HELICOPTERO

		model = glm::mat4(1.0);
		///PARA QUE SE MUEVA EL HELICOPTERO
		///model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::translate(model, glm::vec3(mainWindow.getdesplazamientohelice(), 5.0f, 6.0f));
		spotLights[3].SetPos(glm::vec3(mainWindow.getdesplazamientohelice(),6.0f,6.0f));
		spotLights2[3].SetPos(glm::vec3(mainWindow.getdesplazamientohelice(),6.0f,6.0f));



		//spotLights[3].SetPos(glm::vec3(mainWindow.getdesplazamientohelice(),5.0f,6.0f));

		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();



		////paractica 08
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.0f, 3.5f));
		//		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 3.5f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puerta.RenderModel();


/////
		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
/////gema

model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f,-0.5f, 15.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		gema.RenderModel();




		//Agave �qu� sucede si lo renderizan antes del coche y el helic�ptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
