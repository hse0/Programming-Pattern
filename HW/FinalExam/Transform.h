#pragma once

#include "Object.h"

namespace Transform
{
    struct Vertex
    {
        float x;
        float y;
    };

    struct Vector
    {
        float x_meter;
        float y_meter;
    };

    Vertex MoveVertex(Vertex point, Vector meter);
    Vertex RotateVertex(Vertex point, float angle_degree);
    Vertex ScaleVertex(Vertex point, Vector meter);
};

void updateEnemyPosition(float& x, float speed, float deltaTime);
void updateStarPosition(float& x, float speed, float deltaTime);
void resetEnemyPositions(EnemyBlock& enemy, float resetThreshold);
void resetStarPosition(float& x, float resetThreshold, float newX);
void applyGravityAndJump(float& posY, float& velocityY, bool& isJumping, float gravity, float deltaTime);
float randomFloat(float min, float max);