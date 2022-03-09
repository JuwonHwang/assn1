#pragma once
#include "spriteGroup.h"
#include "shapes.h"
#include <string>

class Cannon : public PolygonSprite {
private:
	Position muzzle;

public:
    Cannon(std::string _name, Color* _color, Position _position, Positions _vertices, Position _muzzle) : PolygonSprite(_name, _color, _position, _vertices) {
		muzzle = _muzzle;
	}

};