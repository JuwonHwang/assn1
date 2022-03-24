#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "colors.h"

#define PI (3.14159265359f)
#define PI2 (6.28318530718f)

typedef glm::mat4 Transform;
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
    
    void setPosition(Position _position) { // 위치를 받아 자신의 위치를 변경
        position = _position;
    }

    const glm::vec3 getVelocity() {
        return vel;
    }

    void setVelocity(glm::vec3 _vel) {
        vel = _vel;
    }

    const glm::vec3 getAccel() {
        return acc;
    }

    void setAccel(glm::vec3 _acc) {
        acc = _acc;
    }

    const float getRotation() {
        return rotation;
    }

    void setRotation(float _rotation) {
        rotation = _rotation;
        while (rotation > PI2) {
            rotation -= PI2;
        }
    }

    virtual const glm::vec4 getRectangle(const Position _position, const float _rotaiton) { return glm::vec4(); };
    virtual void draw(const Position _position, const float _rotaiton) {}; // virtual method - 자신을 화면에 그리는 함수

    virtual void move(const Position _position) { // virtual method - 자신의 위치을 이동하는 함수
        setPosition(getPosition() + _position);
    }

    virtual const float rotate(const float theta) { // virtual method - 회전을 위한 함수
        setRotation(getRotation() + theta);
        return getRotation();
    }

    virtual void update(void) { // virtual method - 위치, 형태 등을 업데이트를 위한 함수
        position += vel;
        vel += acc;
    }
};


class ColoredSprite : public Sprite {
private:
    Color color; // 색상

public:
    ColoredSprite(Color _color, std::string _name, Position _position) : Sprite(_name, _position) {
        color = _color;
    }

    Color getColor() { // 자신의 색상을 반환
        return color;
    }

};


class PolygonSprite : public ColoredSprite {
private:
    Positions vertices; // Polygon의 vertices를 저장하기 위한 멤버

public:
    PolygonSprite(std::string _name, Color _color, Position _position) : ColoredSprite(_color, _name, _position) {};
    PolygonSprite(std::string _name, Color _color, Position _position, Positions _vertices) : ColoredSprite(_color, _name, _position) {
        vertices = _vertices;
    }

    virtual void draw(const Position _position, const float _rotaiton) { // 자신(polygon sprite)을 화면에 그리는 함수
        Color _color = getColor();
        glColor3f(_color[0], _color[1], _color[2]);
        glBegin(GL_POLYGON);
        for (size_t i = 0; i < vertices.size(); i++)
        {
            Transform transform = Transform(1.0f);
            transform = glm::translate(transform, _position); 
            transform = glm::rotate(transform, _rotaiton + getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::translate(transform, getPosition());
            glm::vec4 drawPosition = transform * glm::vec4(vertices[i], 1);
            /*std::cout << "Name : " << getName()
                << " x : " << drawPosition[0]
                << " y : " << drawPosition[1]
                << " z : " << drawPosition[2]
                << std::endl;*/
            glVertex3f(drawPosition[0], drawPosition[1], drawPosition[1]);
        }
        glEnd();
    }

    virtual const glm::vec4 getRectangle(const Position _position, const float _rotaiton) {
        try
        {
            Transform transform0 = Transform(1.0f);
            transform0 = glm::translate(transform0, _position + getPosition());
            transform0 = glm::rotate(transform0, _rotaiton + getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec4 drawPosition0 = transform0 * glm::vec4(vertices[0], 1);
            float left = drawPosition0[0];
            float right = drawPosition0[0];
            float top = drawPosition0[1];
            float bottom = drawPosition0[1];
            for (size_t i = 1; i < vertices.size(); i++)
            {
                Transform transform = Transform(1.0f);
                transform = glm::translate(transform, _position + getPosition());
                transform = glm::rotate(transform, _rotaiton + getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
                glm::vec4 drawPosition = transform * glm::vec4(vertices[i], 1);
                left = std::min(left, drawPosition[0]);
                right = std::max(right, drawPosition[0]);
                top = std::max(top, drawPosition[1]);
                bottom = std::min(bottom, drawPosition[1]);
            }
            return glm::vec4(left, right, top, bottom);
        }
        catch (const std::exception&)
        {

        }
    }
};

