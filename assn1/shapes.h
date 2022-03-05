#pragma once
#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "colors.h"

#define PI (3.14159265359f)
#define PI2 (6.28318530718f)

typedef glm::vec3 Position;
typedef std::vector<glm::vec3> Positions;

namespace Shape
{
    Positions Rectangle(const float width, const float height, const float x, const float y) {
        const glm::vec3 center = glm::vec3(x, y, 0.0f);
        return {
            glm::vec3(0.0f, 0.0f, 0.0f) - center,
            glm::vec3(0.0f, height, 0.0f) - center,
            glm::vec3(width, height, 0.0f) - center,
            glm::vec3(width, 0.0f, 0.0f) - center,
        };
    }

    Positions Circle(const float radius, const float x, const float y, const float accuracy = 1.0f) {
        const glm::vec3 center = glm::vec3(x, y, 0.0f);
        Positions position = {};
        int count = 24 * accuracy;
        for (int i = 0; i < count; i++) {
            position.push_back(glm::vec3(radius * cosf(PI2 * i / count), radius * sinf(PI2 * i / count), 0.0f) + center);
        }
        return position;
    }

    Positions Ellipse(const float width, const float height, const float x, const float y, const float accuracy = 1.0f) {
        const glm::vec3 center = glm::vec3(x, y, 0.0f);
        Positions position = {};
        int count = 24 * accuracy;
        for (int i = 0; i < count; i++) {
            position.push_back(glm::vec3(width * cosf(PI2 * i / count), height * sinf(PI2 * i / count), 0.0f) + center);
        }
        return position;
    }
}
