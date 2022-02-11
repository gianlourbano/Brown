#pragma once
#include "../../brown.hpp"

namespace brown
{
    /*
        state class for managing scenes basically.
        the user needs to implement all the virtual functions
        whenever he creates custom states.
    */
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

        entity create_entity();

    protected:
        state(){};
        WINDOW *win;
        brown::brain brain;
        std::vector<entity> m_entities{};
    };

}