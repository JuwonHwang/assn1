#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "sprite.h"


class SpriteGroup {
private:
    std::vector<Sprite*> sprites;
    std::vector<SpriteGroup*> subGroups;
public:
    SpriteGroup() {};
    ~SpriteGroup() {
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            delete subGroups[i];
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            delete sprites[i];
        }
    }

    size_t addSprite(Sprite* subSprite) {
        sprites.push_back(subSprite);
        return sprites.size();
    }

    size_t addSubGroup(SpriteGroup* subGroup) {
        subGroups.push_back(subGroup);
        return subGroups.size();
    }

    void draw(void) {
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            subGroups[i]->draw();
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            sprites[i]->draw();
        }
    }

    void move(const Position _position) {
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            subGroups[i]->move(_position);
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            sprites[i]->move(_position);
        }
    }
};