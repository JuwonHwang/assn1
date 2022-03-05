#pragma once
#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "colors.h"

typedef glm::vec3 Position;
typedef std::vector<glm::vec3> Positions;

namespace Shape
{
    Positions Rectangle(float width, float height, bool centered = false) {
        glm::vec3 center = glm::vec3(centered ? width/2 : 0, centered ? height / 2 : 0, 0.0f);
        return {
            glm::vec3(0.0f, 0.0f, 0.0f) - center,
            glm::vec3(0.0f, height, 0.0f) - center,
            glm::vec3(width, height, 0.0f) - center,
            glm::vec3(width, 0.0f, 0.0f) - center,
        };
    }
}
