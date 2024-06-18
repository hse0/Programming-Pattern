//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색
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
bool isRightDragging = false;
bool isLeftDragging = false;
double lpos = 0.0;

double xpos = 0.0;
double ypos = 0.0;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightMouseButtonPressed = true;
            isRightDragging = false;
            // 마우스 오른쪽 버튼을 누르면 빨간색으로 설정
            
        }
        else if (action == GLFW_RELEASE)
        
            rightMouseButtonPressed = false;
            // 마우스 오른쪽 버튼을 떼었을 때 배경을 검은색으로 설정
      
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseButtonPressed = true;
            isLeftDragging = false;
            // 마우스 왼쪽 버튼을 누르면 녹색으로 설정
        }
        
        else if (action == GLFW_RELEASE)
        
            leftMouseButtonPressed = false;
            // 마우스 왼쪽 버튼을 떼었을 때 배경을 검은색으로 설정
           
        
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (rightMouseButtonPressed && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        isRightDragging = true;
        isLeftDragging = false;
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); 
    }

    else if(leftMouseButtonPressed && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        isRightDragging = false;
        isLeftDragging = true;
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        isRightDragging = false;
        lpos = 0.0;

        
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main(void)
{
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패 " << std::endl;
        return -1;
    }
    GLFWwindow* window=glfwCreateWindow(1280, 768, "OpenGL Window", NULL, NULL);

    if (!window)
    { 
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSwapInterval(1);
    // 초기 배경을 검은색으로 설정
    

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        
        if (rightMouseButtonPressed)
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }// Red if only right button is down
        else if (leftMouseButtonPressed)
        {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
        }
        else {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Default to black if no mouse button is pressed
        }
        // OpenGL 설정: 배경을 현재 설정된 색으로 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 현재 화면을 화면에 표시
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}