#pragma once
#include "MathUtils.h"

using rgba_t = uint32_t;

inline glm::vec4 RGBAToColor(const rgba_t& rgba) {
    glm::vec4 color;

    color.r = ((rgba >> 24) & 0xff) / 255.0f;
    color.g = ((rgba >> 16) & 0xff) / 255.0f;
    color.b = ((rgba >> 8) & 0xff) / 255.0f;
    color.a = ((rgba >> 0) & 0xff) / 255.0f;

    return color;
}

inline rgba_t ColorToRGBA(const glm::vec4& color) {
    rgba_t rgba = 0;

    rgba |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24;
    rgba |= uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16;
    rgba |= uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8;
    rgba |= uint8_t(glm::clamp(color.a, 0.0f, 1.0f) * 255) << 0;

    return rgba;
}