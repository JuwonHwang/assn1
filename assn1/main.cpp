#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "tank.h"

std::vector<SpriteGroup> allGroups = {}; // 모든 그룹을 저장할 벡터

void init(void) {
    Tank* tank = new Tank(); // 탱크 생성
    allGroups.push_back(*tank); // 탱크를 화면에 출력할 그룹에 추가
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기 
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i].draw(); // 모든 스프라이트 그리기
    }
    glFlush(); // 출력 버퍼 비우기
}

void specialkeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        std::cout << "left";
        for (size_t i = 0; i < allGroups.size(); i++)
        {
            allGroups[i].move(glm::vec3(-0.01f, 0.0f, 0.0f));
        }
        break;
    case GLUT_KEY_RIGHT:
        std::cout << "right";
        for (size_t i = 0; i < allGroups.size(); i++)
        {
            allGroups[i].move(glm::vec3(0.01f, 0.0f, 0.0f));
        }
        break;
    case ' ':
        std::cout << "spacebar";
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        std::cout << "spacebar";
        break;
    }
    //glutPostRedisplay();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
    init(); // 초기화

    glutCreateWindow("Bored Students - Assn1");
    glutDisplayFunc(renderScene); // 화면 출력함수 설정
    glutSpecialFunc(specialkeyboard);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}