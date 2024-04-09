
#pragma comment(lib, "Opengl32.lib")  // Opengl32.lib 라이브러리를 사용하기
#include <GLFW/glfw3.h> 
#include <iostream>  //C++의 표준 입력 및 출력 스트림을 지원하는 헤더 파일인 iostream을 포함하는 것

int width = 1200; // 화면의 너비를 초기값으로 1200
int height = 900; // 화면의 높이를 초기값으로 900
float zoom = 1.0f; // 화면의 확대/축소 비율을 나타내며, 초기값으로 1.0 설정하기
double SposX, SposY; // 마우스 이벤트에서 사용될 마우스의 현재 위치를 나타냄
bool dragging = false; // 마우스 드래그 동작 여부를 나타내며, 초기값으로 false 설정
bool zoomingIn = false; // 현재 화면이 확대 중인지 여부를 나타내며, 초기값으로 false 설정
float cameraX = 0.0f; // 카메라 X 위치를 나타내며 , 초기값으로 0.0 을 설정
float cameraY = 0.0f; // 카메라 y 위치를 나타내며 , 초기값으로 0.0 을 설정

void framebuffer_size_callback(GLFWwindow* window, int wh, int ht) { // 높이와 너비를 매개 변수 wh,ht 로 받음
    width = wh;
    height = ht;
    glViewport(0, 0, width, height); // 그래픽을 디자인 하는 공간
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) { // 이 함수는 GLFW 윈도우 포인터와 눌린 마우스 버튼 액션 그리고 모드를 매개변수로 받음
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        dragging = true; // 드래깅 시작
        zoomingIn = false; // 확대 중이 아님
        glfwGetCursorPos(window, &SposX, &SposY); // 마우스의 현재 위치를 가져와 SposX.SposY 변수에 저장
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { // 만약 눌린 마우스의 버튼이 오른쪽 버튼이고, 눌린 상태인 경우에 실행됨
        dragging = true; // 드래깅 시작
        zoomingIn = true; // 확대중임
        glfwGetCursorPos(window, &SposX, &SposY); // 마우스의 현재 위치를 가져와 SPosx, SposY 변수에 저장
    }
    else if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_RELEASE) { // 만약 눌린 마우스의 버튼이 왼쪽 또는 오른쪽 버튼이고 버튼을 떼었을때 실시
        dragging = false; // 드래깅을 종료함
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) { // GLFW 윈도우 포인터와 마우스 커서의 새로운 x,y 위치를 매개변수로 받음
    if (dragging) { // 만약 드래깅 중인 상태라면
        float sen = 0.01f; // sen 변수를 0.01 로 설정하여 감도를 정의함.
        float deltaX = xpos - SposX; // 마우스의 x 위치 변화량 계산
        float deltaY = ypos - SposY; // 마우스의 x 위치 변화량 계산
        if (zoomingIn) { // 만약 확대중인 상태라면
            if (deltaX > 0) { // 마우스가 오른쪽으로 이동 했을 때:
                zoom *= (1.0f + sen * deltaX); // 확대를 하고 확대가 일정 수준 이하로 줄어들지 않도록 조정함
                if (zoom <= 0.03f)
                {
                    zoom = 0.03f;
                }
            }
            else if (deltaX < 0) { //  마우스가 왼쪽으로 이동했을 때:
                zoom /= (1.0f - sen * deltaX);
                if (zoom <= 0.03f) // 축소가 일정 수준이하로 줄어들지 않도록 조정
                {
                    zoom = 0.03f;
                }
            }
        }
        else { // 확대 중이 아니라면 
            cameraX -= sen * deltaX; // 카메라의 x 위치를 마우스 이동량에 따라 조절함
            cameraY += sen * deltaY; // 카메라의 y 위치를 마우스 이동량에 따라 조절함
        }
        SposX = xpos; // 이전 마우스 x 위치를 현재 위치로 업데이트
        SposY = ypos; // 이전 마우스 y 위치를 현재 위치로 업데이트
    }
}

void setProjection() { // 투영 행렬을 설정하기
    glMatrixMode(GL_PROJECTION); // 이후의 행렬 연산이 투영 행렬에 적용됨
    glLoadIdentity(); // 현재 행렬을 단위 행렬로 초기화
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f); // 좌우 하상 최소 투영 크기. 최대 투영 크기 
    glMatrixMode(GL_MODELVIEW); // 행렬 모드를 다시 GL_MODEVLEW 로 변경
}

void draw() {
    

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); // RGB
    glVertex2f(0.0, -0.5); // x 좌요 -1~1 사이에서 시작하기
    glVertex2f(0.5, -0.8);
    glVertex2f(0.3, -0.3);
    glVertex2f(0.8, 0.1);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.0,  0.8);
    glVertex2f(-0.2, 0.1);
    glVertex2f(-0.8, 0.1);
    glVertex2f(-0.3, -0.3);
    glVertex2f(-0.5, -0.8);
    glVertex2f(0.0, -0.5); // 마지막 좌표를 추가하기

    glEnd();  // 블록 종료

   
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Counting Star", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // 이 함수는 현재 OpenGL 컨텍스트로 사용할 윈도우를 설정
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 이 함수는 윈도우의 프레임 버퍼 크기가 변경 될때 콜백 함수를 등록
    glfwSetMouseButtonCallback(window, mouse_button_callback); // 이 함수는 마우스 버튼 이벤트가 발생시 호촐될 콜백 함수를 등록
    glfwSetCursorPosCallback(window, cursor_pos_callback); // 이 함수는 마우스 커서의 위치가 변경될 때 호출될 콜백 함수를 등록

    glViewport(0, 0, width, height); // OPenGL의 뷰포트를 설정 

    //첫번쨰 매개 변수는 뷰포트의 왼쪽 모서리의 x 좌표를 나타냄
    //두번째 매개변수는 뷰포트의 아래쪽 모서리의 y 좌표를 나타냄
    //세 번째 매개변수는 뷰포트의 너비를 나타냄
    // 네번째 매개변수는 뷰포트의 높이를 나타냄
    while (!glfwWindowShouldClose(window)) { // 윈도우가 닫혀야 하는지 여부 확인

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // 현재 지정된 버퍼를 지우는데 사용

        setProjection(); // 투영 행렬을 설정하는 함수를 호출

        glLoadIdentity(); // 현재 행렬을 단위 행렬로 초기화
        glTranslatef(-cameraX, -cameraY, -5.0f); // 카메라 위치에 따라 모든 객체를 이동시키는 변환을 적용
        glScalef(zoom, zoom, 1.0f); // 확대/ 축소 변환을 적용
        

        // 삼각형 그리기
        draw(); 

        glfwSwapBuffers(window); // 렌더링 결과를 윈도우에 표시
        glfwPollEvents(); // 이벤트 처리 . 이 함수는 현재 발생한 이벤트를 검사하고 이벤트 큐에서 해당 이벤트 제거
    }

    glfwTerminate(); // GLFW 종료하기
    return 0; // 프로그램을 정상적으로 종료하기
} 