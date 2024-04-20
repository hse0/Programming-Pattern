#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include "MSList.h"
#include "Star.hpp"


float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

MSList<MObject*> list;

int initialize()
{

	MObject* temp[300];
	for (int i = 0; i < 300; i++) {
		temp[i] = new Star();
		list.add(temp[i]);
		std::cout << "리스트생성!: " << list.get_size() << std::endl;
		//실행시키면 리스트 생성
	}
	return 0;
}
int release()
{
	for (int i = 0; i < list.get_size(); i++) {
		delete list[i];
		std::cout << "리스트삭제!: " << i + 1 << std::endl;
		//끄면 리스트 삭제
	}
	list.clear();
	return 0;
}

int update()
{
	return 0;
}

int render()
{
	glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i <300; i++)
	{

		MObject* object = new MObject();
		list.add(object); 

		MObject* a = list[i];
		a->render();
	}



	return 0;
}

int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		render();
		glfwSwapBuffers(window);
	}

	release();
	
	
	glfwTerminate();
	return 0;

}