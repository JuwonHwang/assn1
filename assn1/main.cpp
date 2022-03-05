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
        PolygonSprite* polygonSp = new PolygonSprite(
            white, // color
            glm::vec3(0.3f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.1f, 0.1f, true)); // Shape
        this->upperBody.addSprite(polygonSp);
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

    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(renderScene);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}
