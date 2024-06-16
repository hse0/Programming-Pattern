#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include "Object.h" // Include your header file
#include "Transform.h" // Include the header file for Transform and StarManager

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
    ObstacleManager obstacleManager(2, 100.0f, -200.0f, 400.0f, 600.0f); // 최대 2개의 장애물, 속도 -200, 최소 간격 400, 최대 간격 600
    StarManager starManager(5, -66.67f, 800, 600); // 5개의 별, 속도 -66.67 (장애물 속도의 1/3)

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float deltaTime = 0.016f; // Assuming 60 FPS, so ~16ms per frame

        floor.draw(100.0f, 800);
        player.draw(400.0f, 300.0f, 50.0f, 3.0f); // Player at (400, 300) with size 50cm and 3cm border

        starManager.update(deltaTime);
        for (const auto& star : starManager.getStars()) {
            Star starObj;
            starObj.draw(star.x, star.y, star.width); // 별 그리기
        }

        obstacleManager.update(deltaTime);
        for (const auto& obstacle : obstacleManager.getObstacles()) {
            enemyBlock.draw(obstacle.x, obstacle.y, obstacle.width, obstacle.height); // 장애물 크기
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
