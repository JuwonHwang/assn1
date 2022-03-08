#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "colors.h"

#define PI (3.14159265359f)
#define PI2 (6.28318530718f)

typedef glm::mat<3,3,float> Transform;
typedef glm::vec3 Position;
typedef std::vector<glm::vec3> Positions;

/*
화면에 표시되는 물체를 그리기 위한 기본 class
*/
class Sprite { 
private:
    std::string name = "none";
    Position position = glm::vec3(0.0f, 0.0f, 0.0f); // 위치
    glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f); // velocity
    glm::vec3 acc = glm::vec3(0.0f, 0.0f, 0.0f); // acceleration
    float rotation = 0.0f; // 회전
    
public:
    Sprite() {}
    Sprite(std::string _name, Position _position) {
        position = _position;
        name = _name;
    }

    const std::string getName() {
        return name;
    }

    const Position getPosition() { // 자신의 위치를 반환
        return position;
    }
    
    void setPostion(Position _position) { // 위치를 받아 자신의 위치를 변경
        position = _position;
    }

    float getRotation() {
        return rotation;
    }

    void setRotation(float _rotation) {
        rotation = std::max(std::min(_rotation, PI2), 0.0f);
    }

    virtual void draw(Position _position) {}; // virtual method - 자신을 화면에 그리는 함수
    virtual void move(const Position _position) { // virtual method - 자신의 위치을 이동하는 함수
        setPostion(getPosition() + _position);
    }
    virtual void rotate(float theta) {}; // virtual method - 회전을 위한 함수
    virtual void update(void) { // virtual method - 위치, 형태 등을 업데이트를 위한 함수
        position += vel;
        vel += acc;
    }
};


class ColoredSprite : public Sprite {
private:
    Color color; // 색상

public:
    ColoredSprite(Color* _color, std::string _name, Position _position) : Sprite(_name, _position) {
        color = *_color;
    }

    Color getColor() { // 자신의 색상을 반환
        return color;
    }

};


class PolygonSprite : public ColoredSprite {
private:
    Positions vertices; // Polygon의 vertices를 저장하기 위한 멤버

public:
    PolygonSprite(std::string _name, Color* _color, Position _position) : ColoredSprite(_color, _name, _position) {};
    PolygonSprite(std::string _name, Color* _color, Position _position, Positions _vertices) : ColoredSprite(_color, _name, _position) {
        vertices = _vertices;
    }

    virtual void draw(Position _position) { // 자신(polygon sprite)을 화면에 그리는 함수
        glColor3f(getColor()[0], getColor()[1], getColor()[2]);
        glBegin(GL_POLYGON);
        for (size_t i = 0; i < vertices.size(); i++)
        {
            glVertex3f(_position[0] + getPosition()[0] + vertices[i][0],
                       _position[1] + getPosition()[1] + vertices[i][1],
                       _position[2] + getPosition()[2] + vertices[i][2]);
        }
        glEnd();
    }

    virtual void rotate(float theta) {
        
    }

    virtual void update(void) {};
};
