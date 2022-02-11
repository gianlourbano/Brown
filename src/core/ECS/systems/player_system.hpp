#pragma once
#include <ncurses.h>
#include "../system.hpp"
#include "../../brain.hpp"

namespace brown {
    class player_system : public system {
        public:
            void handle_player_events(char c, WINDOW *win, brain *br);
    };
}