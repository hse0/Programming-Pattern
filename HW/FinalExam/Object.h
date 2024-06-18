#pragma once
#include <GLFW/glfw3.h>

void PixelToOpenGL(float FloorXpixel, float FloorYpixel);

class Object {
public:
    float posX, posY, width, height;
    Object(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
        : posX(x), posY(y), width(w), height(h) {}

    virtual void OnCollisionEnter(Object& other) {}
};

class Player : public Object {
public:
    float velocityY = 0.0f; 
    bool isJumping = false;

    Player() : Object(100.0f, 450.0f, 50.0f, 50.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawPlayer();
    }
    void drawPlayer();
};

class EnemyBlock : public Object {
public:
    float posX1 = 800.0f;
    float posX2 = 1600.0f;
    float posX3 = 2400.0f;
    float posX4 = 2500.0f;

    EnemyBlock() : Object(0.0f, 0.0f, 50.0f, 100.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawCac();
    }
    void drawCac();
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        drawFloor();
    }
    void drawFloor();
};

class Star : public Object {
public:
    float size;

    Star() : Object(), size(0.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawStar();
    }
    void drawStar() const;
};

int PhysicsAABB(const Object& A, const Object& B);