#pragma once
/* pa windows
#include<stdio.h>
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
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getangulorueda() { return angulorueda; }
//cofre
GLfloat getangulocofre() { return angulocofre; }
///DESPLAZAMIENTO
GLfloat getdesplazamiento(){ return desplazamiento;}
///helice
GLfloat getdesplazamientohelice(){ return mueveHelix;}

GLfloat getArrLuz(){return arreglo;}

	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	////rueda
GLfloat angulorueda=0.0f;
///cofre
GLfloat angulocofre=0.0f;
///desplazamiento
GLfloat desplazamiento= 0.0f;
///movimiento helice
GLfloat mueveHelix;
GLfloat arreglo=0.0f;

	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

