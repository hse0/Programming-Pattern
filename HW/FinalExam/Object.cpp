#include "Object.h"
#include "Transform.h"
#include <cmath> 

void PixelToOpenGL(float FloorXpixel, float FloorYpixel) {
    int Width = 800;
    int Height = 600;

    float FloorXgl = 2.0f * (FloorXpixel / Width) - 1.0f;
    float FloorYgl = 1.0f - 2.0f * (FloorYpixel / Height);

    glVertex2f(FloorXgl, FloorYgl);
}

void Player::drawPlayer() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(posX - 3.0f, posY - 3.0f);
    PixelToOpenGL(posX - 3.0f, posY + height + 3.0f);
    PixelToOpenGL(posX + width + 3.0f, posY + height + 3.0f);
    PixelToOpenGL(posX + width + 3.0f, posY - 3.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(posX, posY);
    PixelToOpenGL(posX, posY + height);
    PixelToOpenGL(posX + width, posY + height);
    PixelToOpenGL(posX + width, posY);
    glEnd();
}

void EnemyBlock::drawCac() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(posX1, 400.0f);
    PixelToOpenGL(posX1, 500.0f);
    PixelToOpenGL(posX1 + width, 500.0f);
    PixelToOpenGL(posX1 + width, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX2, 200.0f);
    PixelToOpenGL(posX2, 500.0f);
    PixelToOpenGL(posX2 + width, 500.0f);
    PixelToOpenGL(posX2 + width, 200.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX3, 400.0f);
    PixelToOpenGL(posX3, 500.0f);
    PixelToOpenGL(posX3 + width, 500.0f);
    PixelToOpenGL(posX3 + width, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(posX4, 200.0f);
    PixelToOpenGL(posX4, 500.0f);
    PixelToOpenGL(posX4 + width, 500.0f);
    PixelToOpenGL(posX4 + width, 200.0f);
    glEnd();
}

void Floor::drawFloor() {
    glColor3f(1.0f, 0.78f, 0.05f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(0.0f, 500.0f);
    PixelToOpenGL(0.0f, 600.0f);
    PixelToOpenGL(800.0f, 600.0f);
    PixelToOpenGL(800.0f, 500.0f);
    glEnd();
}

void Star::drawStar() const {
    float halfSize = size / 4.0f;
    float angle = 72.0f * 3.141592 / 180.0f;
    glColor3ub(255, 255, 0); 

    glBegin(GL_TRIANGLE_FAN);
    PixelToOpenGL(posX, posY); 

    for (int i = 0; i <= 5; ++i) {
        float xVertex = posX + halfSize * cos(i * 2 * angle);
        float yVertex = posY + halfSize * sin(i * 2 * angle);
        PixelToOpenGL(xVertex, yVertex);
    }

    glEnd();
}

int PhysicsAABB(const Object& A, const Object& B) {
    return (A.posX < B.posX + B.width &&
        A.posX + A.width > B.posX &&
        A.posY < B.posY + B.height &&
        A.posY + A.height > B.posY);
}