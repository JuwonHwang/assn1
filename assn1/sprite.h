#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "colors.h"

typedef glm::vec3 Position;
typedef std::vector<glm::vec3> Positions;

class Sprite {
private:
    Position position;
    Color color;
public:
    Sprite() {}
    Sprite(Color* _color, Position _position) {
        color = *_color;
        position = _position;
    }

    Color getColor() {
        return color;
    }

    Position getPosition() {
        return position;
    }
    
    void setPostion(Position _position) {
        position = _position;
    }

    virtual void draw(void) = 0; 
    virtual void move(const Position _position) {
        setPostion(getPosition() + _position);
    }
};


class PolygonSprite : public Sprite {
private:
    Positions vertices;

public:
    PolygonSprite(Color* _color, Position _position) : Sprite(_color, _position) {};
    PolygonSprite(Color* _color, Position _position, Positions _vertices) : Sprite(_color, _position) {
        vertices = _vertices;
    }

    virtual void draw(void) {
        std::cout << vertices.size() << std::endl;
        glColor3f(getColor()[0], getColor()[1], getColor()[2]);
        glBegin(GL_POLYGON);
        for (size_t i = 0; i < vertices.size(); i++)
        {
            glVertex3f(getPosition()[0] + vertices[i][0], 
                       getPosition()[1] + vertices[i][1], 
                       getPosition()[2] + vertices[i][2]);
        }
        glEnd();
    }
};
