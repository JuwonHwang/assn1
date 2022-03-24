#pragma once
#include "spriteGroup.h"
#include "shapes.h"
#include <string>

class Bomb : public SpriteGroup {
private:

public:
    Bomb(std::vector<std::vector<Sprite*>*> _groups, std::string _name, Position _position) : SpriteGroup(_groups, _name, _position) { // ��ź ������

        Color white = Color(1.0f, 1.0f, 1.0f);

        PolygonSprite* ball = new PolygonSprite(
            "ball",
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Circle(0.02f, 0.0f, 0.0f), // Shape
            Shape::Circle(0.02f, 0.0f, 0.0f)); // Mask
        this->addSprite(ball); // SpriteGroup�� Sprite �߰�

        setAccel(glm::vec3(0.0f, -0.001f, 0.0f));
    }

    bool landedChecker() { // ��ź�� ���� ��Ҵ��� Ȯ���ϴ� �Լ�
        if (this->getPosition()[1] <= 0.0f) {
            return true;
        }
        else {
            return false;
        }
    }

    virtual void update() {
        SpriteGroup::update();
        if (landedChecker()) {
            this->kill();
        }
    }
};
