#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "sprite.h"
#include "spriteGroup.h"
#include "shapes.h"

class Tank : public SpriteGroup {
private:
    SpriteGroup upperBody;
    SpriteGroup lowerBody;
    SpriteGroup wheels;
    SpriteGroup gunBarrel;

public:
    Tank() {

        Color* white = new Color(1.0f, 1.0f, 1.0f);

        PolygonSprite* upperSp = new PolygonSprite(
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Circle(0.05f, 0.0f, 0.1f)); // Shape
        PolygonSprite* lowerSp = new PolygonSprite(
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.1f, 0.1f, 0.0f)); // Shape
        upperBody.addSprite(upperSp);
        lowerBody.addSprite(lowerSp);

        for (int i = 0; i < 6; i++) {
            PolygonSprite* wheel = new PolygonSprite(
                white, // color
                glm::vec3((i - 2.5f) * 0.03f, -0.01f, 0.0f), // position
                Shape::Circle(0.015f, 0, 0, 0.5f)); // Shape
            wheels.addSprite(wheel);
        }

        addSubGroup(&upperBody);
        addSubGroup(&lowerBody);
        addSubGroup(&wheels);
        addSubGroup(&gunBarrel);
    }
};

std::vector<SpriteGroup> allGroups = {};

void init(void) {
    Tank* tank = new Tank();
    allGroups.push_back(*tank);
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 
    for (size_t i = 0; i < allGroups.size(); i++)
    {
        allGroups[i].draw();
    }
    glFlush();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
    init();

    glutCreateWindow("Bored Students - Assn1");
    glutDisplayFunc(renderScene);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}
