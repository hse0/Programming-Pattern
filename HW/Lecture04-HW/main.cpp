//������ ������Ʈ��: Lecture04_HW
//idle : ȭ��� ���������� clear
//���콺 ������ KeyDown�ϸ� : ������
//���콺 ������ KeyUp�ϸ� : ���󺹱�
//���콺 ���� KeyDown�ϸ� : ���
//���콺 ���� KeyUp�ϸ� : ���󺹱�
//���콺 ������ KeyDown�ϰ� �巡�� ���̸� : �Ķ���
//���콺 ���� KeyDown�ϰ� �巡�� ���̸� : ����Ÿ��
//������ ������Ʈ��: Lecture04_HW
//idle : ȭ��� ���������� clear
//���콺 ������ KeyDown�ϸ� : ������
//���콺 ������ KeyUp�ϸ� : ���󺹱�
//���콺 ���� KeyDown�ϸ� : ���
//���콺 ���� KeyUp�ϸ� : ���󺹱�
//���콺 ������ KeyDown�ϰ� �巡�� ���̸� : �Ķ���
//���콺 ���� KeyDown�ϰ� �巡�� ���̸� : ����Ÿ��
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
            // ���콺 ������ ��ư�� ������ ���������� ����
            
        }
        else if (action == GLFW_RELEASE)
        
            rightMouseButtonPressed = false;
            // ���콺 ������ ��ư�� ������ �� ����� ���������� ����
      
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseButtonPressed = true;
            isLeftDragging = false;
            // ���콺 ���� ��ư�� ������ ������� ����
        }
        
        else if (action == GLFW_RELEASE)
        
            leftMouseButtonPressed = false;
            // ���콺 ���� ��ư�� ������ �� ����� ���������� ����
           
        
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
        std::cerr << "GLFW �ʱ�ȭ ���� " << std::endl;
        return -1;
    }
    GLFWwindow* window=glfwCreateWindow(1280, 768, "OpenGL Window", NULL, NULL);

    if (!window)
    { 
        std::cerr << "GLFW ������ ���� ����" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSwapInterval(1);
    // �ʱ� ����� ���������� ����
    

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
        // OpenGL ����: ����� ���� ������ ������ �����
        glClear(GL_COLOR_BUFFER_BIT);

        // ���� ȭ���� ȭ�鿡 ǥ��
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}