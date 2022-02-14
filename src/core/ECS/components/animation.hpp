#include "sprite.hpp"

struct animation {
    int clips = 0;
    bool playing;
    int current = 0;
    bool cyclic;
    int time_step;
    std::vector<sprite> animation_clips;
};