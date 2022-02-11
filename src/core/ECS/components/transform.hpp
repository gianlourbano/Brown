#pragma once
#include "../../../math/vec2.hpp"

struct transform {
    vec2 position;
    vec2 scale;
    int direction = 0;
};