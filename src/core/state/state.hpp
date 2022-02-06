#pragma once
#include "../../brown.hpp"

namespace brown
{
    class state
    {
    public:
        virtual void init(engine *game) = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void handle_events(engine *game) = 0;
        virtual void update(engine *game) = 0;
        virtual void draw(engine *game) = 0;

        void change_state(engine *game, state *state) { game->change_state(state); }

        WINDOW *get_win() { return win; }
        void set_win(WINDOW *win) { this->win = win; }

    protected:
        state(){};
        WINDOW *win;
    };

}