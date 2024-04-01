//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색
#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool rightMouseButtonPressed = false;
bool leftMouseButtonPressed = false;
bool isDragging = false;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightMouseButtonPressed = true;
            // 마우스 오른쪽 버튼을 누르면 빨간색으로 설정
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            rightMouseButtonPressed = false;
            // 마우스 오른쪽 버튼을 떼었을 때 배경을 검은색으로 설정
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseButtonPressed = true;
            // 마우스 왼쪽 버튼을 누르면 녹색으로 설정
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            leftMouseButtonPressed = false;
            // 마우스 왼쪽 버튼을 떼었을 때 배경을 검은색으로 설정
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (rightMouseButtonPressed || leftMouseButtonPressed)
    {
        isDragging = true;
        // 마우스 오른쪽 또는 왼쪽 버튼을 누르고 드래그 중일 때 파란색 또는 마젠타로 설정
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파란색
    }
    else
    {
        isDragging = false;
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    // 초기 배경을 검은색으로 설정
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // OpenGL 설정: 배경을 현재 설정된 색으로 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 현재 화면을 화면에 표시
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}