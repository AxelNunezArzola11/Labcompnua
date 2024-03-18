#pragma once
#include<stdio.h>
/* pa windows
#include<glew.h>
#include<glfw3.h>
*/
//linux
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacion5() { return articulacion5; }
	GLfloat getarticulacion6() { return articulacion6; }
	//se agregan las nuevas articulaciones.
	///cabeza
	GLfloat getangulocabeza() { return angulocabeza; }
	//mandibula
	GLfloat getangulomandibula() { return angulomandibula; }

	//patas
	GLfloat getangulopata_delantera_der() { return angulopata_delantera_der; }
	GLfloat getangulopata_delantera_izq() { return angulopata_delantera_izq; }
	GLfloat getangulopata_trasera_der() { return angulopata_trasera_der; }
	GLfloat getangulopata_trasera_izq() { return angulopata_trasera_izq; }
////carro 
//rueda
GLfloat getangulorueda() { return angulorueda; }
//cofre
GLfloat getangulocofre() { return angulocofre; }
///DESPLAZAMIENTO
GLfloat getdesplazamiento(){ return desplazamiento;}



	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax,rotay,rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, 
	articulacion6;
		///  angulo cabeza
		GLfloat angulocabeza =0.0f;


		/// angulo mandibula
		GLfloat angulomandibula=0.0f;
////////////pata delantera derecha
GLfloat angulopata_delantera_der=0.0f;
///PATA delantera izq
GLfloat angulopata_delantera_izq=0.0f;
	/// PATA TRASERA DER
GLfloat angulopata_trasera_der=0.0f;
	/// PATA TRASERA IZQ
GLfloat angulopata_trasera_izq=0.0f;
////rueda
GLfloat angulorueda=0.0f;
///cofre
GLfloat angulocofre=0.0f;
///desplazamiento
GLfloat desplazamiento= 0.0f;



	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

