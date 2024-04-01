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
            // ���콺 ������ ��ư�� ������ ���������� ����
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            rightMouseButtonPressed = false;
            // ���콺 ������ ��ư�� ������ �� ����� ���������� ����
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseButtonPressed = true;
            // ���콺 ���� ��ư�� ������ ������� ����
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            leftMouseButtonPressed = false;
            // ���콺 ���� ��ư�� ������ �� ����� ���������� ����
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (rightMouseButtonPressed || leftMouseButtonPressed)
    {
        isDragging = true;
        // ���콺 ������ �Ǵ� ���� ��ư�� ������ �巡�� ���� �� �Ķ��� �Ǵ� ����Ÿ�� ����
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �Ķ���
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

    // �ʱ� ����� ���������� ����
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // OpenGL ����: ����� ���� ������ ������ �����
        glClear(GL_COLOR_BUFFER_BIT);

        // ���� ȭ���� ȭ�鿡 ǥ��
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}