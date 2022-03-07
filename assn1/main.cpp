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
    Tank() { // 탱크 생성자
        // 모든 멤버를 하위 그룹에 추가
        addSubGroup(&upperBody);
        addSubGroup(&lowerBody);
        addSubGroup(&wheels);
        addSubGroup(&gunBarrel);

        Color* white = new Color(1.0f, 1.0f, 1.0f);

        PolygonSprite* upperSp = new PolygonSprite(
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Circle(0.05f, 0.0f, 0.1f)); // Shape
        upperBody.addSprite(upperSp);

        PolygonSprite* lowerSp = new PolygonSprite(
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.1f, 0.1f, 0.0f)); // Shape
        lowerBody.addSprite(lowerSp);

        for (int i = 0; i < 6; i++) {
            PolygonSprite* wheel = new PolygonSprite(
                white, // color
                glm::vec3((i - 2.5f) * 0.03f, -0.01f, 0.0f), // position
                Shape::Circle(0.015f, 0, 0, 0.5f)); // Shape
            wheels.addSprite(wheel);
        }

    }
};

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

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
    init(); // 초기화

    glutCreateWindow("Bored Students - Assn1");
    glutDisplayFunc(renderScene); // 화면 출력함수 설정
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glewInit();
    glutMainLoop();
}
