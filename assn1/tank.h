#pragma once
#include "spriteGroup.h"
#include "shapes.h"
#include <string>

class Tank : public SpriteGroup {
private:
    SpriteGroup upperBody;
    SpriteGroup lowerBody;
    SpriteGroup wheels;
    SpriteGroup gunBarrel;

public:
    Tank(std::string _name, Position _position) : SpriteGroup(_name, _position) { // 탱크 생성자
        // 모든 멤버를 하위 그룹에 추가
        addSubGroup(&upperBody);
        addSubGroup(&lowerBody);
        addSubGroup(&wheels);
        addSubGroup(&gunBarrel);

        Color* white = new Color(1.0f, 1.0f, 1.0f);

        PolygonSprite* upperSp = new PolygonSprite(
            "upperBody",
            white, // color
            glm::vec3(0.0f, 0.1f, 0.0f), // position
            Shape::Circle(0.05f, 0.0f, 0.0f)); // Shape
        upperBody.addSprite(upperSp);

        PolygonSprite* lowerSp = new PolygonSprite(
            "lowerBody",
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.1f, 0.1f, 0.0f)); // Shape
        lowerBody.addSprite(lowerSp);

        for (int i = 0; i < 6; i++) {
            PolygonSprite* wheel = new PolygonSprite(
                "wheel"+std::to_string(i),
                white, // color
                glm::vec3((i - 2.5f) * 0.03f, -0.01f, 0.0f), // position
                Shape::Circle(0.015f, 0, 0, 0.5f)); // Shape
            wheels.addSprite(wheel);
        }

        PolygonSprite* gunBarrelSp = new PolygonSprite(
            "gunBarrel",
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.01f, 0.0f, 0.005f)); // Shape
        gunBarrelSp->rotate(0.1f * PI);
        gunBarrel.addSprite(gunBarrelSp);
        gunBarrel.setPosition(Position(0.0f, 0.1f, 0.0f));

    }

    void rotateGunBarrel(const float dir) {
        gunBarrel.getSprites()[0]->rotate(dir);
    }
};
