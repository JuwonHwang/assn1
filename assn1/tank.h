#pragma once
#include "spriteGroup.h"
#include "shapes.h"

class Tank : public SpriteGroup {
private:
    SpriteGroup upperBody;
    SpriteGroup lowerBody;
    SpriteGroup wheels;
    SpriteGroup gunBarrel;

public:
    Tank() { // ��ũ ������
        // ��� ����� ���� �׷쿡 �߰�
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
