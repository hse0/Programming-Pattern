#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
const float M_PI = 3.14159265358979323846f;

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
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

int setVertexRotation(float x, float y, float angle_degree)
{ 
    float angle = angle_degree / 180 * M_PI;
    glVertex2f(x * cos(angle) - (y * sin(angle)), x * sin(angle) + (y * cos(angle)));
    return 0;
}

int setVertexEarthRotation(float x, float y, float orbit_angle_degree, float rotate_angle_degree, float sun_center_x, float sun_center_y, float orbit_radius)
{ 
    float orbit_angle = orbit_angle_degree * M_PI / 180;
    float rotate_angle = rotate_angle_degree * M_PI / 180;
    float orbit_x = sun_center_x + orbit_radius * cos(orbit_angle);
    float orbit_y = sun_center_y + orbit_radius * sin(orbit_angle);
    glVertex2f(orbit_x + x * cos(rotate_angle) - (y * sin(rotate_angle)), orbit_y + x * sin(rotate_angle) + (y * cos(rotate_angle)));
    return 0;
}

int setVertexStarRotation(float x, float y, float orbit_angle_degree, float rotate_angle_degree, float earth_center_x, float earth_center_y, float orbit_radius)
{ 
    float orbit_angle = orbit_angle_degree * M_PI / 180;
    float rotate_angle = rotate_angle_degree * M_PI / 180;
    float orbit_x = earth_center_x + orbit_radius * cos(orbit_angle);
    float orbit_y = earth_center_y + orbit_radius * sin(orbit_angle);
    glVertex2f(orbit_x + x * cos(rotate_angle) - (y * sin(rotate_angle)), orbit_y + x * sin(rotate_angle) + (y * cos(rotate_angle)));
    return 0;
}

float SunAngle = 0;
float Big_angle = 130;
float Small_angle = 240;
float EarthRotateAngle = 0;
float EarthOrbitAngle = 0;
float StarRotationAngle = 0;
float StarOrbitAngle = 0;

float sunRotation = 360.0f / 30.0f;
float EarthRotation = 360.0f / 10.0f; 
float EarthOrbit= 360.0f / 60.0f;
float StarRotateOrbit = 360.0f / 3.0f;
double previousTime = 0.0;

int render(float deltaTime)
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 217, 102);
    double radius = 0.2;
    for (int i = 0; i < 360; i++)
    {
        double x = radius * cos(i * M_PI / 180);
        double y = radius * sin(i * M_PI / 180);
        setVertexRotation(x, y, SunAngle);
    }
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.77f, 0.35f, 0.06f);
    double rad = 0.2;
    double x[360], y[360];
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180;
        x[i] = rad * cos(angle);
        y[i] = rad * sin(angle);
    }
    for (int i = 0; i < 360; i++)
    {
        setVertexRotation(x[i], y[i], SunAngle);
        setVertexRotation(x[i + 1], y[i + 1], SunAngle);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 230, 153);
    float big_radius = 0.08;
    for (int i = 0; i < 360; i++)
    {
        double x = big_radius * cos(i * M_PI / 180);
        double y = big_radius * sin(i * M_PI / 180);
        setVertexRotation(x + 0.08, y + 0.05, Big_angle);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 192, 0);
    float small_radius = 0.05;
    for (int i = 0; i < 360; i++)
    {
        double x = small_radius * cos(i * M_PI / 180);
        double y = small_radius * 0.27 * sin(i * M_PI / 180);
        setVertexRotation(x + 0.008, y + 0.17, Small_angle);
    }
    glEnd();

    float sun_center_x = 0.0f;
    float sun_center_y = 0.0f;
    float orbit_radius = 0.6f;

    glBegin(GL_POLYGON);
    glColor3ub(91, 155, 213);
    setVertexEarthRotation(-0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(-0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    setVertexEarthRotation(-0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(-0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, 0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    setVertexEarthRotation(0.05f, -0.05f, EarthOrbitAngle, EarthRotateAngle, sun_center_x, sun_center_y, orbit_radius);
    glEnd();

    float earth_center_x = sun_center_x + orbit_radius * cos(EarthOrbitAngle * M_PI / 180);
    float earth_center_y = sun_center_y + orbit_radius * sin(EarthOrbitAngle * M_PI / 180);
    float moon_orbit_radius = 0.15f;
    float star_radius = 0.05f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 242, 0);
    setVertexStarRotation(0.0f, 0.0f, StarOrbitAngle, StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    for (int i = 0; i < 360; i += 72) {
        float x = star_radius * cos(i * M_PI / 180);
        float y = star_radius * sin(i * M_PI / 180);
        setVertexStarRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexStarRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i + 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    }
    setVertexStarRotation(star_radius, 0.0f, StarOrbitAngle, StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 360; i += 72) {
        float x = star_radius * cos(i * M_PI / 180);
        float y = star_radius * sin(i * M_PI / 180);
        setVertexStarRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i - 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexStarRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexStarRotation(x, y, StarOrbitAngle, i + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
        setVertexStarRotation(x * 0.5f, y * 0.5f, StarOrbitAngle, i + 36 + StarRotationAngle, earth_center_x, earth_center_y, moon_orbit_radius);
    }
    glEnd();

    SunAngle -= sunRotation * deltaTime;
    Big_angle -= sunRotation * deltaTime;
    Small_angle -= sunRotation * deltaTime;
    EarthOrbitAngle += EarthOrbit * deltaTime;
    EarthRotateAngle += EarthRotation * deltaTime;
    StarRotationAngle += StarRotateOrbit * deltaTime;
    StarOrbitAngle -= StarRotateOrbit * deltaTime;

    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    previousTime = glfwGetTime(); 

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime(); 
        float deltaTime = static_cast<float>(currentTime - previousTime); 
        previousTime = currentTime; 
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        render(deltaTime);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
