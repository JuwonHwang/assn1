#pragma once
#include "spriteGroup.h"
#include "shapes.h"
#include "bomb.h"
#include <string>

class Tank : public SpriteGroup {
private:
    float hp = 100;
    SpriteGroup* upperBody;
    SpriteGroup* lowerBody;
    SpriteGroup* wheels;
    SpriteGroup* gunBarrel;
    int maxBombs = 1;
    std::vector<Sprite*> bombs;
    int shootTimer = 0;

public:
    Tank(std::vector<std::vector<Sprite*>*> _groups, 
        std::string _name, 
        Position _position,
        Color _color ) : SpriteGroup(_groups, _name, _position) { // 탱크 생성자
        // 모든 멤버를 하위 그룹에 추가
        upperBody = new SpriteGroup();
        lowerBody = new SpriteGroup();
        wheels = new SpriteGroup();
        gunBarrel = new SpriteGroup();

        Color white = _color;
        Color frame_color = Color(0.5f, 0.5f, 0.5f);

        PolygonSprite* upperSp = new PolygonSprite(
            "upperBody",
            white, // color
            glm::vec3(0.0f, 0.1f, 0.0f), // position
            Shape::Circle(0.05f, 0.0f, 0.0f)); // Shape
        upperBody->addSprite(upperSp);

        PolygonSprite* lowerSp = new PolygonSprite(
            "lowerBody",
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.1f, 0.1f, 0.0f)); // Shape
        lowerBody->addSprite(lowerSp);

        for (int i = 0; i < 6; i++) {
            PolygonSprite* wheel = new PolygonSprite(
                "wheel"+std::to_string(i),
                white, // color
                glm::vec3((i - 2.5f) * 0.03f, -0.01f, 0.0f), // position
                Shape::Circle(0.015f, 0, 0, 0.5f)); // Shape
            PolygonSprite* wheel_frame = new PolygonSprite(
                "wheel_frame" + std::to_string(i),
                frame_color, // color
                glm::vec3((i - 2.5f) * 0.03f, -0.01f, 0.0f), // position
                Shape::Rectangle(0.03f, 0.003f, 0.015f, 0.0015f)); // Shape
            wheels->addSprite(wheel);
            wheels->addSprite(wheel_frame);
        }


        PolygonSprite* gunBarrelSp = new PolygonSprite(
            "gunBarrel",
            white, // color
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            Shape::Rectangle(0.2f, 0.01f, 0.0f, 0.005f)); // Shape
        gunBarrelSp->rotate(0.1f * PI);
        gunBarrel->addSprite(gunBarrelSp);
        gunBarrel->setPosition(Position(0.0f, 0.1f, 0.0f));

        addSubGroup(upperBody);
        addSubGroup(lowerBody);
        addSubGroup(wheels);
        addSubGroup(gunBarrel);
    }

    void rotateGunBarrel(const float dir) {
        gunBarrel->getSprites()[0]->rotate(dir);
    }

    const Position getBarrelFrontPos() {
        Transform transform = Transform(1.0f);
        transform = glm::translate(transform, getPosition());
        transform = glm::translate(transform, gunBarrel->getPosition());
        transform = glm::translate(transform, gunBarrel->getSprites()[0]->getPosition());
        transform = glm::rotate(transform, gunBarrel->getSprites()[0]->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::vec4 drawPosition = transform * glm::vec4(0.2f, 0.005f, 0.0f, 1);
        return drawPosition;
    }

    void shoot(std::vector<std::vector<Sprite*>*> allGroup) {
        if (bombs.size() < maxBombs) {
            allGroup.push_back(&bombs);
            Bomb* bomb = new Bomb(allGroup, "bomb", getBarrelFrontPos()); // 폭탄 생성
            const float dir = gunBarrel->getSprites()[0]->getRotation();
            glm::vec3 _vel = glm::vec3(cosf(dir), sinf(dir), 0) * 0.03f;
            bomb->setVelocity(_vel);
            //bombs.push_back(bomb);
        }
    }

    bool checkCollision(const float speed) {
        //bool left = (getPosition()[0] - 0.1f + speed) <= -1.0f;
        //bool right = (getBarrelFrontPos()[0] + speed) >= 1.0f;
        glm::vec4 rect = getRectangle(Position(0.0f, 0.0f, 0.0f), 0.0f);
        //std::cout << rect[0] << ", " << rect[1] << std::endl;
        bool left = (rect[0] + speed) <= -1.0f;
        bool right = (rect[1] + speed) >= 1.0f;
        return ((speed < 0) && left || (speed > 0) && right);
    }

    void shift(const float speed) {
        if (!checkCollision(speed)) {
            move(glm::vec3(speed, 0.0f, 0.0f));
        }
    }

    int getShootTimer(void) {
        return shootTimer;
    }

    void setShootTimer(int _timer) {
        shootTimer = _timer;
    }

    bool randShoot() {
        shootTimer += rand() % 10;
        if (shootTimer > 100) {
            shootTimer = 0;
            return true;
        }
        else {
            return false;
        }
    }

};
