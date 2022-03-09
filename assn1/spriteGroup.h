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
    std::vector<std::vector<Sprite*>*> groups;

public:
    SpriteGroup() {};
    SpriteGroup(std::vector<std::vector<Sprite*>*> _groups, std::string _name, Position _position) : Sprite(_name, _position) {
        groups = _groups;
        std::cout << getName() << " - group size : " << _groups.size() << std::endl;
        for (size_t i = 0; i < _groups.size(); i++) {
            _groups[i]->push_back(this);
        }
    };

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

    void kill() {
        for (size_t i = 0; i < groups.size(); i++) {
            groups[i]->erase(std::remove(groups[i]->begin(), groups[i]->end(), this), groups[i]->end());
        }
        delete this;
    }

    size_t addSprite(Sprite* subSprite) { // 그룹에 sprite 추가
        sprites.push_back(subSprite);
        return sprites.size();
    }

    size_t addSubGroup(SpriteGroup* subGroup) { // 그룹에 하위 그룹 추가
        subGroups.push_back(subGroup);
        return subGroups.size();
    }

    std::vector<Sprite*> getSprites() {
        return sprites;
    }

    std::vector<SpriteGroup*> getSubGroup() {
        return subGroups;
    }

    virtual void draw(const Position _position, const float _rotation) { // 그룹의 모든 요소를 화면에 그리는 함수
        for (size_t i = 0; i < subGroups.size(); i++)
        {
            subGroups[i]->draw(_position + getPosition(), _rotation + getRotation());
        }
        for (size_t j = 0; j < sprites.size(); j++)
        {
            sprites[j]->draw(_position + getPosition(), _rotation + getRotation());
        }
    }

    virtual void update(void) {
        setPosition(getPosition() + getVelocity());
        setVelocity(getVelocity() + getAccel());
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