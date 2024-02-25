//Pr�ctica 2 semestre 2024-2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
/*
#include <glew.h>
#include <glfw3.h>*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include<gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
///nuevos vertexs shaders
//shaders nuevos se crear�an ac�
static const char* vazul_shader = "shaders/azul_shader.vert";
static const char* vcafe_shader = "shaders/cafe_shader.vert";
static const char* vroja_shader = "shaders/roja_shader.vert";
static const char* vverde_shader = "shaders/verde_shader.vert";
static const char* vverde_oscuro_shader = "shaders/verde_oscuro_shader.vert";


float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	// debo de poner mis iniciales con un color por vertice y cada letra de un color diferente
		//X			Y			Z			R		G		B
		0.2f,			0.5f,		0.0f,      1.0f,	0.0f,	0.0f,
		0.2f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.2f,			0.5f,		0.0f,      1.0f,	0.0f,	0.0f,

		0.25f,			0.5f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.2f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.8f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.8f,		0.0f,	   1.0f,	0.0f,	0.0f,

		0.25f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.8f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.8f,		0.0f,	   1.0f,	0.0f,	0.0f,

		0.35f,			0.8f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.4f, 			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.65f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.6f,		0.0f,	   1.0f,	0.0f,	0.0f,
		
		0.35f,			0.6f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.25f,			0.65f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.65f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.6f,		0.0f,	   1.0f,	0.0f,	0.0f,
		0.35f,			0.75f,		0.0f,	   1.0f,	0.0f,	0.0f,


		0.35f,			0.5f,		0.0f,	  1.0f,		0.0f,	0.0f,
		0.4f,			0.5f,		0.0f,	  1.0f,		0.0f,	0.0f,
        0.35f,			0.75f,		0.0f,	  1.0f,		0.0f,	0.0f,
		0.4f,			0.75f,		0.0f,	  1.0f,		0.0f,	0.0f,
		0.4f,			0.5f,		0.0f,	  1.0f,		0.0f,	0.0f,

///LETRA N RECTANGULO 1
 		0.45f, 			0.5f, 		0.0f,	  0.0f,		1.0f,	0.0f,
    	0.45f, 			0.8f, 		0.0f, 	  0.0f,		1.0f,	0.0f,
    	0.5f, 			0.8f, 		0.0f, 	  0.0f,		1.0f,	0.0f,

    // Segundo triángulo
    	0.5f, 			0.8f, 		0.0f, 	  0.0f,		1.0f,	0.0f,
    	0.5f, 			0.5f, 		0.0f, 	  0.0f,		1.0f,	0.0f,
    	0.45f, 			0.5f,	    0.0f, 	  0.0f,		1.0f,	0.0f,

///diagonal
	 	0.5f, 			0.8f, 		0.0f,	  0.0f,		1.0f,	0.0f,
    	0.6f,		    0.5f, 		0.0f, 	  0.0f,		1.0f,	0.0f,
    	0.55f, 			0.5f, 		0.0f, 	  0.0f,		1.0f,	0.0f,
///otro rectangulo
		0.6f,			0.5f,		0.0f, 	  0.0f,		1.0f,	0.0f,
		0.6f,			0.8f,		0.0f, 	  0.0f,		1.0f,	0.0f,
		0.65f,			0.8f,		0.0f, 	  0.0f,		1.0f,	0.0f,

		0.65f,			0.8f,		0.0f,	  0.0f,		1.0f,	0.0f,
		0.65f,			0.5f,		0.0f,	  0.0f,		1.0f,	0.0f,
		0.6f,			0.5f,		0.0f,	  0.0f,		1.0f,	0.0f,
////  letra D
		0.7f, 			0.8f, 		0.0f,	  0.0f,		0.0f,	1.0f,     
    	0.75f, 			0.8f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.7f, 			0.5f, 		0.0f,     0.0f,		0.0f,	1.0f,
    	0.75f, 			0.8f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.5f, 		0.0f,	  0.0f,		0.0f,	1.0f,

		0.7f, 			0.5f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.8f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.75f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.75f, 		0.0f,	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.8f, 		0.0f,	  0.0f,		0.0f,	1.0f,

		0.85f, 			0.8f, 		0.0f, 	  0.0f,		0.0f,	1.0f,	 
    	0.85f, 			0.75f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.8f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.75f,		 0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.9f, 			0.75f, 		 0.0f,	  0.0f,		0.0f,	1.0f,

		0.85f, 			0.75f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.9f, 			0.75f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.55f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.9f, 			0.75f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.55f, 		0.0f, 	  0.0f,		0.0f,	1.0f,

		0.9f, 			0.55f,		 0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.55f, 		 0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.9f, 			0.55f, 		 0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.5f, 		 0.0f,	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.55f, 		0.0f,	  0.0f,		0.0f,	1.0f,

		0.75f, 			0.5f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.5f,		 0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.75f, 			0.55f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.55f, 		0.0f, 	  0.0f,		0.0f,	1.0f,
    	0.85f, 			0.5f, 		0.0f, 	  0.0f,		0.0f,	1.0f,

	};
	///AND  VERTICES 450
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 450);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);


	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);
	
	
/// se crean los nuevos para la ejercicio
///triangulo azul
GLfloat  vert_triang_azul []={
	//X			Y			Z			R		G		B
	-1.0f,	  -1.0f,		0.5f,	   0.0f,	0.0f,	1.0f,
	1.0f,	  -1.0f,		0.5f,	   0.0f,	0.0f,	1.0f,
	0.0f,	   1.0f,		0.5f,	   0.0f,	0.0f,	1.0f,
};
MeshColor* triang_azul = new MeshColor();
	triang_azul->CreateMeshColor(vert_triang_azul, 18);
	meshColorList.push_back(triang_azul);
	///triang verde
	GLfloat vert_triang_verde []={
		//X			Y			Z		R		G		B
	-1.0f,	  -1.0f,		0.5f,	   0.0f,	0.5f,	0.0f,
	1.0f,	  -1.0f,		0.5f,	   0.0f,	0.5f,	0.0f,
	0.0f,	   1.0f,		0.5f,	   0.0f,	0.5f,	0.0f,
	};
	MeshColor* triang_verde = new MeshColor();
	triang_verde->CreateMeshColor(vert_triang_verde, 18);
	meshColorList.push_back(triang_verde);
//cuadrado rojo
GLfloat vert_cuad_rojo []={
		//X			Y			Z		R		G		B
	-0.5f,	  -0.5f,		0.5f,	   1.0f,	0.0f,	0.0f,
	0.5f,	  -0.5f,		0.5f,	   1.0f,	0.0f,	0.0f,
	0.5f,	   0.5f,		0.5f,	   1.0f,	0.0f,	0.0f,

	-0.5f,	  -0.5f,		0.5f,	   1.0f,	0.0f,	0.0f,
	0.5f,	  0.5f,		   0.5f,	   1.0f,	0.0f,	0.0f,
	-0.5f,	   0.5f,		0.5f,	   1.0f,	0.0f,	0.0f,
	};
MeshColor* cuad_rojo = new MeshColor();
	cuad_rojo->CreateMeshColor(vert_cuad_rojo, 36);
	meshColorList.push_back(cuad_rojo);

///trinag verde  verde
GLfloat vert_cuad_verde []={
		//X			Y			Z		R		G		B
	-0.5f,	  -0.5f,		0.5f,	   0.0f,	2.0f,	0.0f,
	0.5f,	  -0.5f,		0.5f,	   0.0f,	2.0f,	0.0f,
	0.5f,	   0.5f,		0.5f,	   0.0f,	2.0f,	0.0f,

	-0.5f,	  -0.5f,		0.5f,	   0.0f,	2.0f,	0.0f,
	0.5f,	  0.5f,			0.5f,	   0.0f,	2.0f,	0.0f,
	-0.5f,	   0.5f,		0.5f,	   0.0f,	2.0f,	0.0f,
	};


MeshColor* cuad_verde = new MeshColor();
	cuad_verde->CreateMeshColor(vert_cuad_verde, 36);
	meshColorList.push_back(cuad_verde);
//cuadrado cafe
GLfloat vert_cuad_cafe []={
		//X			Y			Z		R		G		B
	-0.5f,	  -0.5f,		0.5f,	   0.478f, 0.255f, 0.067f,
	0.5f,	  -0.5f,		0.5f,	   0.478f, 0.255f, 0.067f,
	0.5f,	   0.5f,		0.5f,	   0.478f, 0.255f, 0.067f,

	-0.5f,	  -0.5f,		0.5f,	   0.478f, 0.255f, 0.067f,
	0.5f,	  0.5f,			0.5f,	   0.478f, 0.255f, 0.067f,
	-0.5f,	   0.5f,		0.5f,	   0.478f, 0.255f, 0.067f,
	};
MeshColor* cuad_cafe = new MeshColor();
	cuad_cafe->CreateMeshColor(vert_cuad_cafe, 36);
	meshColorList.push_back(cuad_cafe);

}
void CreateShaders()
{
////ESTO SE TIENE QUE HACER PARA CADA NUEVO SHADER CON SU FRAGMENT SHADER
//LISTAS ES UN FIFO PRIMERO EN ENTRAR PRIMERO EN SALIR
	Shader *shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	///se crean los shaders
	Shader *shader3 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader3->CreateFromFiles(vazul_shader, fShader);
	shaderList.push_back(*shader3);

	Shader *shader4 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader4->CreateFromFiles(vcafe_shader, fShader);
	shaderList.push_back(*shader4);

	Shader *shader5 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader5->CreateFromFiles(vroja_shader, fShader);
	shaderList.push_back(*shader5);

	Shader *shader6 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader6->CreateFromFiles(vverde_shader, fShader);
	shaderList.push_back(*shader6);

	Shader *shader7 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader7->CreateFromFiles(vverde_oscuro_shader, fShader);
	shaderList.push_back(*shader7);


}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	///GLUint entero para oPENGL 
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
	///letras
		
/*
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	
		meshColorList[0]->RenderMeshColor(); 
		*/
	
		
		// piramide azul									
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
	
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor(); 
		
//  piramide verde izquierdo 
shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.55f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();
//piramide verde derecho
shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.55f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();


///  cubo rojo
shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -4.0f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 0.2f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor();
//// cubo verde
/*
shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, 0.2f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.2f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[]->RenderMeshColor(); 
		*/
////cuadrado cafe parte 1
shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.9f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();
////cuadrado cafe parte 2
shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.9f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[7]->RenderMeshColor();	

//cuadrado verde izquierdo
shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor();
///cuadrado verde derecho
shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor();

///cuadrado verde centro
shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor();

/*
		//Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList
		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

//traingulo verde izquierdo





shaderList[0].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, 0.2f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.2f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();*/

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/