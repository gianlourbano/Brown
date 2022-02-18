#include "sprite.hpp"
#include "../../../math/vec2.hpp"

struct animation {
    int clips = 0;
    bool playing;
    int current = 0;
    bool cyclic;
    int time_step;
    vec2 offset;
    std::string name;
};