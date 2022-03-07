#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "tank.h"

std::vector<SpriteGroup> allGroups = {}; // ��� �׷��� ������ ����

void init(void) {
    Tank* tank = new Tank(); // ��ũ ����
    allGroups.push_back(*tank); // ��ũ�� ȭ�鿡 ����� �׷쿡 �߰�
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // ȭ�� ����� 
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i].draw(); // ��� ��������Ʈ �׸���
    }
    glFlush(); // ��� ���� ����
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}