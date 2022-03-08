#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "colors.h"

typedef glm::mat<3,3,float> Transform;
typedef glm::vec3 Position;
typedef std::vector<glm::vec3> Positions;


/*
화면에 표시되는 물체를 그리기 위한 기본 class
*/
class Sprite { 
private:
    Position position; // 위치
    Color color; // 색상
public:
    Sprite() {}
    Sprite(Color* _color, Position _position) {
        color = *_color;
        position = _position;
    }

    Color getColor() { // 자신의 색상을 반환
        return color;
    }

    Position getPosition() { // 자신의 위치를 반환
        return position;
    }
    
    void setPostion(Position _position) { // 위치를 받아 자신의 위치를 변경
        position = _position;
    }

    virtual void draw(void) = 0; // virtual method - 자신을 화면에 그리는 함수
    virtual void move(const Position _position) { // virtual method - 자신의 위치을 이동하는 함수
        setPostion(getPosition() + _position);
    }
    virtual void rotate(void) = 0; // virtual method - 회전을 위한 함수
    virtual void update(void) = 0; // virtual method - 위치, 형태 등을 업데이트를 위한 함수
};


class PolygonSprite : public Sprite {
private:
    Positions vertices; // Polygon의 vertices를 저장하기 위한 멤버

public:
    PolygonSprite(Color* _color, Position _position) : Sprite(_color, _position) {};
    PolygonSprite(Color* _color, Position _position, Positions _vertices) : Sprite(_color, _position) {
        vertices = _vertices;
    }

    virtual void draw(void) { // 자신(polygon sprite)을 화면에 그리는 함수
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
    
    virtual void rotate(void) {};
    virtual void update(void) {};
};
