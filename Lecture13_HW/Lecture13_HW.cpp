#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

const float GRAVITY = 9.8f;
const float JUMP_VELOCITY = 5.0f;
const float GROUND_Y = -0.95f; // 땅의 y 위치를 조정하여 두께를 얇게 함
const float SQUARE_SIZE = 0.1f;

struct Square {
    float x, y;
    float velocityY;
};

// Initialize the square above the ground at y = 1.0f
Square square = { 0.0f, 1.0f, 0.0f };

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && square.y <= GROUND_Y + SQUARE_SIZE / 2 + 0.01f)
    {
        square.velocityY = JUMP_VELOCITY;  // Jump when space is pressed
    }
}

void update(float deltaTime)
{
    // Apply gravity
    square.velocityY -= GRAVITY * deltaTime;
    // Update position
    square.y += square.velocityY * deltaTime;

    // Collision with ground
    if (square.y - SQUARE_SIZE / 2 < GROUND_Y)
    {
        // Adjust position
        square.y = GROUND_Y + SQUARE_SIZE / 2;
        // Stop falling
        square.velocityY = 0;
    }
}

void render()
{
    // Draw background
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ground
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, GROUND_Y);
    glVertex2f(1.0f, GROUND_Y);
    glVertex2f(1.0f, GROUND_Y - 0.1f); // 땅의 두께를 얇게 조정
    glVertex2f(-1.0f, GROUND_Y - 0.1f);
    glEnd();

    // Draw square (회색)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(square.x - SQUARE_SIZE / 2, square.y - SQUARE_SIZE / 2);
    glVertex2f(square.x + SQUARE_SIZE / 2, square.y - SQUARE_SIZE / 2);
    glVertex2f(square.x + SQUARE_SIZE / 2, square.y + SQUARE_SIZE / 2);
    glVertex2f(square.x - SQUARE_SIZE / 2, square.y + SQUARE_SIZE / 2);
    glEnd();
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "Dinosaur Run", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        // Get delta time
        static double previousTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        // Update
        update(deltaTime);

        // Render
        glLoadIdentity();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}