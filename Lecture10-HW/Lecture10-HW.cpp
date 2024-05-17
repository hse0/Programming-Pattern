#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>

const double PI = 3.14159265358979323846;

int main() {
    // Initialize GLFW
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(900, 700, "Canvas Rotation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Get the size of the window
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Set up viewport
        glViewport(0, 0, width, height);

        // Set up projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);

        // Set up modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Center coordinates
        double centerX = width / 2.0;
        double centerY = height / 2.0;

        // Distance from center to blue rectangle
        double blueRectDistance = 300;

        // Distance from blue rectangle to grey rectangle
        double greyRectDistance = 60; // Increased distance from blue rectangle

        // Initial angles
        static double redRect = 0;
        static double blueRect = 0;
        static double greyRect = 0;
        static double smallCircleRotation = 0; // ȸ�� ����

        // Drawing code
        // Red circle
        glColor3ub(255, 217, 102); // RGB color setting
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++) {
            double theta = i * PI / 180.0;
            glVertex2f(centerX + 25.0 * cos(theta), centerY + 25.0 * sin(theta));
        }
        glEnd();

        // Draw small circle inside the big circle
        glColor3ub(255, 230, 153); // RGB color setting for the small circle
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++) {
            double theta = i * PI / 180.0;
            glVertex2f(centerX - 10.0 + 10.0 * cos(theta), centerY + 10.0 * sin(theta)); // Adjust the radius accordingly
        }
        glEnd();

        // ���� ���� ū �� �Ʒ��ʿ� ��ġ�ϰ� ȸ�� ��ȯ �߰�
        glPushMatrix();
        double smallCircleCenterX = centerX + 15.0; // ���� ���� �߽� X ��ǥ
        double smallCircleCenterY = centerY + 12.0; // ���� ���� �߽� Y ��ǥ (ū �� �Ʒ���)

        glTranslatef(smallCircleCenterX, smallCircleCenterY, 0); // ȸ�� �߽��� ���� ���� �߽����� �̵�
        glRotatef(150.0, 0.0, 0.0, 1.0); // 30�� �ð� �ݴ� �������� ȸ��

        glColor3ub(255, 230, 153); // ���� ���� �� ����
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 360; i >= 0; i--) { // ������ ���ҽ��� �ݴ� �������� ȸ��
            double theta = i * PI / 180.0; // ���� ���
            glVertex2f(7.0 * cos(theta), 3.0 * sin(theta)); // ȸ�� �߽��� �������� ��ǥ ���
        }
        glEnd();

        glPopMatrix(); // ���� ��ķ� ����

        // Draw outline for the big circle
        glColor3ub(197, 90, 17); // RGB color setting for the outline
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++) {
            double theta = i * PI / 180.0;
            glVertex2f(centerX + 25.0 * cos(theta), centerY + 25.0 * sin(theta));
        }
        glEnd();

        // Blue rectangle
        glColor3f(0.0, 0.0, 1.0);
        glPushMatrix();
        glTranslatef(centerX, centerY, 0.0); // Blue rectangle's initial position at the center
        glRotatef(-blueRect * 180.0 / PI, 0.0, 0.0, 1.0);
        glTranslatef(-blueRectDistance, 0.0, 0.0); // Blue rectangle's distance from the center
        glBegin(GL_QUADS);
        glVertex2f(-25.0, -25.0);
        glVertex2f(25.0, -25.0);
        glVertex2f(25.0, 25.0);
        glVertex2f(-25.0, 25.0);
        glEnd();
        glPopMatrix();

        // Draw star
        glColor3ub(255, 242, 0); // Yellow color
        glPushMatrix();
        glTranslatef(centerX, centerY, 0.0);
        glRotatef(-blueRect * 180.0 / PI, 0.0, 0.0, 1.0);
        glTranslatef(-blueRectDistance - greyRectDistance, 0.0, 0.0);
        glRotatef(greyRect * 180.0 / PI, 0.0, 0.0, -1.0);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0); // Center
        for (int i = 0; i < 5; ++i) { // Five vertices of the star
            double angle = (4 * PI / 5) * i + PI / 2; // Adjust angle
            double x = 30 * cos(angle); // Adjust size
            double y = 30 * sin(angle); // Adjust size
            glVertex2d(x, y);
            angle += (2 * PI / 5); // Move to the next vertex
            x = 7.5 * cos(angle + PI / 5); // Adjust size and angle
            y = 7.5 * sin(angle + PI / 5); // Adjust size and angle
            glVertex2d(x, y);
        }
        glEnd();

        glPopMatrix();

        // Update angles
        redRect += PI / 100;
        blueRect += PI / 200;
        greyRect -= PI / 200; // Rotate the grey rectangle clockwise around the center
        smallCircleRotation += 1.0; // ���� ���� ȸ�� ���� ������Ʈ (�ð� �ݴ� �������� ȸ��)

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
