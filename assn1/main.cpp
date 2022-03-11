#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "tank.h"
#include "bomb.h"
#include "land.h"

std::vector<Sprite*> allGroups = {}; // 모든 그룹을 저장할 벡터
Tank* tank;

void init(void) {
    new Land({ &allGroups }, "land", glm::vec3(0.0f, 0.0f, 0.0f));
    tank = new Tank({ &allGroups }, "tank", glm::vec3(0.0f, 0.0f, 0.0f)); // 탱크 생성
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

//void disappearing_bomb() {
//    bomb_exist = false;
//    allGroups.pop_back();
//    tank->removeBomb(bomb);
//    delete bomb;
//}

//void shooting_bomb(int a) {
//    if (bomb_exist == true) {
//        glutTimerFunc(10, shooting_bomb, 0);
//        bomb->move(glm::vec3(0.01f, 0.0f, 0.0f));
//        if (bomb->getPosition()[0] > 0.7f) {
//            disappearing_bomb();
//        }
//        glutPostRedisplay();
//    }
//}

void specialkeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        std::cout << "left";
        if (!tank->tankLeftOutChecker()) {
            tank->move(glm::vec3(-0.01f, 0.0f, 0.0f));
        }
        break;
    case GLUT_KEY_RIGHT:
        std::cout << "right";
        if (!tank->tankRightOutChecker()) {
            tank->move(glm::vec3(0.01f, 0.0f, 0.0f));
        }
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        std::cout << "spacebar";
        if (tank != 0)
        {
            tank->shoot({ &allGroups }); // 폭탄 생성
        }
        //if (bomb != 0) {
        //    //bomb_exist = true;
        //    //allGroups.push_back(bomb);
        //    //shooting_bomb(0);
        //}
        break;

    case 'k':
        tank->kill();
        tank = 0;

    //case 't': // tank 위치 프린트 테스트
    //    Position tank_position = tank->getPosition();
    //    std::cout << tank_position[0] << tank_position[1] << tank_position[2];
    }
    glutPostRedisplay();
}

void timer(int value) {
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i]->update();
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
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
    glutTimerFunc(0, timer, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}