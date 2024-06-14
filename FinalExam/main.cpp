#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include "Object.h" // Include your header file

GLFWwindow* initWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    return window;
}

void setProjection(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    GLFWwindow* window = initWindow(800, 600, "Google Dino Run Copy Game");
    if (!window) return -1;

    setProjection(800, 600);

    Player player;
    EnemyBlock enemyBlock;
    Floor floor;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        floor.draw(100.0f, 800);
        player.draw(400.0f, 300.0f, 50.0f, 3.0f); // Player at (400, 300) with size 50cm and 3cm border

        // Draw obstacles
        enemyBlock.draw(200.0f, 100.0f, 50.0f, 100.0f); // Low obstacle 1
        enemyBlock.draw(600.0f, 100.0f, 50.0f, 100.0f); // Low obstacle 2
        enemyBlock.draw(200.0f, 300.0f, 50.0f, 300.0f); // High obstacle 1
        enemyBlock.draw(600.0f, 300.0f, 50.0f, 300.0f); // High obstacle 2

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}