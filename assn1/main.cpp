#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "tank.h"
#include "bomb.h"

std::vector<SpriteGroup*> allGroups = {}; // 모든 그룹을 저장할 벡터
Tank* tank;
Bomb* bomb;

void init(void) {
    tank = new Tank("tank", glm::vec3(0.0f, 0.0f, 0.0f)); // 탱크 생성
    allGroups.push_back(tank); // 탱크를 화면에 출력할 그룹에 추가
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // ȭ�� ����� 
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i]->draw(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f); // 모든 스프라이트 그리기
    }
    glFlush(); // ��� ���� ����
}

void specialkeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        std::cout << "left";
        tank->move(glm::vec3(-0.01f, 0.0f, 0.0f));
        break;
    case GLUT_KEY_RIGHT:
        std::cout << "right";
        tank->move(glm::vec3(0.01f, 0.0f, 0.0f));
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        std::cout << "spacebar";
        bomb = new Bomb("bomb", tank->getPosition()); // 폭탄 생성
        allGroups.push_back(bomb);
        break;

    case 't':
        Position tank_position = tank->getPosition();
        std::cout << tank_position[0] << tank_position[1] << tank_position[2];
    }
    glutPostRedisplay();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
    init(); // �ʱ�ȭ

    glutCreateWindow("Bored Students - Assn1");
    glutDisplayFunc(renderScene); // ȭ�� ����Լ� ����
    glutSpecialFunc(specialkeyboard);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}