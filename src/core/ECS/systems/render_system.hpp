#include "../system.hpp"
#include "../../brain.hpp"
#include <ncurses.h>

namespace brown
{
    class render_system : public brown::system
    {
    public:
        void draw(WINDOW *win, brain *br);
    };
}