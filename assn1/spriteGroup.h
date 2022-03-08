#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "sprite.h"

/*
* sprite를 모아 한번에 그리는 것을 처리하기 위한 Tree 자료구조
*/
class SpriteGroup : public Sprite {
private:
    std::vector<Sprite*> sprites;
    std::vector<SpriteGroup*> subGroups;
public:
    SpriteGroup() {};
    SpriteGroup(std::string _name, Position _position) : Sprite(_name, _position) {};

    ~SpriteGroup() { // 할당해제
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            delete subGroups[i];
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            delete sprites[i];
        }
    }

    size_t addSprite(Sprite* subSprite) { // 그룹에 sprite 추가
        sprites.push_back(subSprite);
        return sprites.size();
    }

    size_t addSubGroup(SpriteGroup* subGroup) { // 그룹에 하위 그룹 추가
        subGroups.push_back(subGroup);
        return subGroups.size();
    }

    virtual void draw(const Position _position) { // 그룹의 모든 요소를 화면에 그리는 함수
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            subGroups[i]->draw(_position + getPosition());
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            sprites[i]->draw(_position + getPosition());
        }
    }

    virtual void update(void) {
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            subGroups[i]->update();
        }
        for (size_t i = 0; i < sprites.size(); i++)
        {
            sprites[i]->update();
        }
    }
};