#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Object {
public:
    virtual void OnCollisionEnter(Object& other) {
    }
};

// Derived classes
class Player : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void draw(float centerX, float centerY, float sizeInCm, float borderThicknessInCm) {
        // Draw the player square
        float halfSize = sizeInCm / 2.0f;
        float halfBorder = borderThicknessInCm / 2.0f;
        float innerX1 = centerX - halfSize;
        float innerX2 = centerX + halfSize;
        float innerY1 = centerY - halfSize;
        float innerY2 = centerY + halfSize;
        float outerX1 = innerX1 - halfBorder;
        float outerX2 = innerX2 + halfBorder;
        float outerY1 = innerY1 - halfBorder;
        float outerY2 = innerY2 + halfBorder;

        // Draw filled red square for player
        glColor3ub(255, 0, 0); // Red color for player
        glBegin(GL_QUADS);
        glVertex2f(innerX1, innerY1);
        glVertex2f(innerX2, innerY1);
        glVertex2f(innerX2, innerY2);
        glVertex2f(innerX1, innerY2);
        glEnd();

        // Draw the border around the player square
        glColor3ub(0, 0, 0); // Black color for border
        glBegin(GL_QUADS);
        glVertex2f(outerX1, outerY1);
        glVertex2f(outerX2, outerY1);
        glVertex2f(outerX2, innerY1);
        glVertex2f(outerX1, innerY1);

        glVertex2f(outerX2, outerY1);
        glVertex2f(outerX2, outerY2);
        glVertex2f(innerX2, outerY2);
        glVertex2f(innerX2, outerY1);

        glVertex2f(innerX1, outerY2);
        glVertex2f(innerX2, outerY2);
        glVertex2f(innerX2, innerY2);
        glVertex2f(innerX1, innerY2);

        glVertex2f(outerX1, innerY1);
        glVertex2f(innerX1, innerY1);
        glVertex2f(innerX1, innerY2);
        glVertex2f(outerX1, innerY2);
        glEnd();
    }
};

class EnemyBlock : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void draw(float centerX, float groundLevel, float widthInCm, float heightInCm) {
        float halfWidth = widthInCm / 2.0f;
        float halfHeight = heightInCm / 2.0f;

        // Calculate coordinates
        float x1 = centerX - halfWidth;
        float x2 = centerX + halfWidth;
        float y1 = groundLevel; // Bottom of the obstacle
        float y2 = groundLevel + heightInCm; // Top of the obstacle

        glColor3ub(0, 255, 0); // Green color for obstacle
        glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glEnd();
    }
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void draw(float groundLevelInCm, int windowWidth) {
        glColor3ub(255, 200, 15); // Color for floor
        glBegin(GL_QUADS);
        glVertex2f(0, groundLevelInCm);
        glVertex2f(windowWidth, groundLevelInCm);
        glVertex2f(windowWidth, 0);
        glVertex2f(0, 0);
        glEnd();
    }
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void draw(float centerX, float centerY, float sizeInCm) {
        float halfSize = sizeInCm / 2.0f;
        float angle = 72.0f * M_PI / 180.0f; // 72 degrees in radians
        glColor3ub(255, 255, 0); // Yellow color for star

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY); // Center of star

        for (int i = 0; i <= 5; ++i) {
            float x = centerX + halfSize * cos(i * 2 * angle);
            float y = centerY + halfSize * sin(i * 2 * angle);
            glVertex2f(x, y);
        }

        glEnd();
    }
};

int PhysicsAABB(Object A, Object B) {
    return 0;
}
