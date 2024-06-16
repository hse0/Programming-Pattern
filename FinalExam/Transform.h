#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

class Transform {
public:
    float x, y;
    float speedX;
    float width;
    float height;

    Transform(float x, float y, float speedX, float width, float height)
        : x(x), y(y), speedX(speedX), width(width), height(height) {}

    void update(float deltaTime) {
        x += speedX * deltaTime;
        if (x < -width) { // 화면 왼쪽을 벗어나면
            x = 800 + (std::rand() % 200); // 화면 오른쪽에서 다시 나타남
            height = (std::rand() % 2 == 0) ? 100.0f : 300.0f; // 높이를 다시 랜덤 설정
        }
    }
};

class ObstacleManager {
private:
    std::vector<Transform> obstacles;
    int maxObstacles;
    float groundLevel;
    float obstacleSpeed;
    float minGap;
    float maxGap;

public:
    ObstacleManager(int maxObstacles, float groundLevel, float speed, float minGap, float maxGap)
        : maxObstacles(maxObstacles), groundLevel(groundLevel), obstacleSpeed(speed), minGap(minGap), maxGap(maxGap) {
        std::srand(std::time(0));
        float initialX = 800.0f;
        for (int i = 0; i < maxObstacles; ++i) {
            float x = initialX + minGap * i + (std::rand() % static_cast<int>(maxGap - minGap)); // 장애물 초기 위치를 랜덤하게 설정
            float height = (std::rand() % 2 == 0) ? 100.0f : 300.0f; // 높이를 100cm 또는 300cm로 랜덤 설정
            obstacles.emplace_back(x, groundLevel, obstacleSpeed, 50.0f, height);
        }
    }

    void update(float deltaTime) {
        for (auto& obstacle : obstacles) {
            obstacle.update(deltaTime);
            if (obstacle.x < -obstacle.width) {
                float lastX = obstacle.x;
                if (!obstacles.empty()) {
                    lastX = obstacles.back().x;
                }
                obstacle.x = lastX + minGap + (std::rand() % static_cast<int>(maxGap - minGap)); // 장애물이 화면을 벗어나면 다시 오른쪽에서 랜덤 위치에 나타남
                obstacle.height = (std::rand() % 2 == 0) ? 100.0f : 300.0f; // 높이를 다시 랜덤 설정
            }
        }
    }

    const std::vector<Transform>& getObstacles() const {
        return obstacles;
    }
};

class StarManager {
private:
    std::vector<Transform> stars;
    float starSpeed;
    int windowWidth;
    int windowHeight;

public:
    StarManager(int numStars, float starSpeed, int windowWidth, int windowHeight)
        : starSpeed(starSpeed), windowWidth(windowWidth), windowHeight(windowHeight) {
        std::srand(std::time(0));
        for (int i = 0; i < numStars; ++i) {
            float x = std::rand() % windowWidth;
            float y = windowHeight - (std::rand() % (windowHeight / 2)); // 하늘에 나타나게
            float size = (std::rand() % 40) + 10; // 10cm ~ 50cm 크기로 랜덤 설정
            stars.emplace_back(x, y, starSpeed, size, size);
        }
    }

    void update(float deltaTime) {
        for (auto& star : stars) {
            star.update(deltaTime);
            if (star.x < -star.width) {
                star.x = windowWidth + (std::rand() % 200);
                star.y = windowHeight - (std::rand() % (windowHeight / 2));
                star.width = star.height = (std::rand() % 40) + 10; // 크기를 다시 랜덤 설정
            }
        }
    }

    const std::vector<Transform>& getStars() const {
        return stars;
    }
};
