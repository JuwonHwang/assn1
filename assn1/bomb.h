#pragma once
#include "spriteGroup.h"
#include "shapes.h"
#include <string>

class Bomb : public SpriteGroup {
private:

public:
    Bomb(std::string _name, Position _position) : SpriteGroup(_name, _position) { // ÆøÅº »ý¼ºÀÚ

        Color* white = new Color(1.0f, 1.0f, 1.0f);

        PolygonSprite* ball = new PolygonSprite(
            "ball",
            white, // color
            glm::vec3(0.8f, 0.0f, 0.0f), // position
            Shape::Circle(0.02f, 0.0f, 0.0f)); // Shape
        this->addSprite(ball); // SpriteGroup¿¡ Sprite Ãß°¡

        

    }
};
