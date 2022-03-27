#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "tank.h"
#include "bomb.h"
#include "land.h"
#include "collision.h"

std::vector<Sprite*> allGroups = {};
Tank* tank;
Tank* enemy;

void init(void) {
    new Land({ &allGroups }, "land", glm::vec3(0.0f, 0.0f, 0.0f));
    tank = new Tank({ &allGroups }, "tank", glm::vec3(0.0f, 0.0f, 0.0f), Color(0.5f, 1.0f, 0.5f));
    enemy = new Tank({ &allGroups }, "enemy", glm::vec3(0.7f, 0.0f, 0.0f), Color(0.7f, 0.5f, 0.5f));
    enemy->rotateGunBarrel(0.8 * PI);
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i]->draw(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    }
    glFlush();
}


void specialkeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        tank->setVelocity(Position(-0.01f,0.0f,0.0f));
        break;
    case GLUT_KEY_RIGHT:
        tank->setVelocity(Position(0.01f, 0.0f, 0.0f));
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        if (tank != 0)
        {
            tank->shoot({ &allGroups });
        }
        break;
    case 'k':
        tank->kill();
        tank = 0;
        break;
    case 'w':
        //std::cout << "angle up";
        tank->angleUpGunBarrel();
        break;
    case 's':
        //std::cout << "angle down";
        tank->angleDownGunBarrel();
        break;
    case 'e':
        //std::cout << "power up";
        if (tank->power < 5) {
            tank->power += 1;
        }
        tank->updateGunBarrelColor();
        break;
    case 'q':
        //std::cout << "power down";
        if (tank->power > 1) {
            tank->power -= 1;
        }
        tank->updateGunBarrelColor();
        break;
    }

    glutPostRedisplay();
}

void timer(int value) {
    if (enemy->randShoot()) {
        //enemy->shoot({ &allGroups });
    }
    checkAllCollision(allGroups);
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
    init();

    glutCreateWindow("Bored Students - Assn1");
    glutDisplayFunc(renderScene);
    glutSpecialFunc(specialkeyboard);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}