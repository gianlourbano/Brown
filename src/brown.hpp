#pragma once
#include <ncurses.h>
#include <vector>
#include "debug/debugger.hpp"

//////
#include "core/event/event_manager.hpp"
#include "core/ECS/entity_manager.hpp"
#include "core/ECS/component_manager.hpp"
#include "core/ECS/system_manager.hpp"

namespace brown
{
    class state;

    class engine
    {
    public:
        void init(int width, int height);
        void cleanup();

        void change_state(state *state);
        void push_state(state *state);
        void pop_state();

        void handle_events();
        void update();
        void draw();

        bool running() { return m_running; }
        void quit();

        WINDOW *get_std_screen() { return stdscreen; }
        WINDOW *get_current_screen() { return current_screen; }
        void set_current_screen(WINDOW *win) { current_screen = win; }

    private:
        // standard screen output
        WINDOW *stdscreen;
        WINDOW *current_screen;

        // the stack of states
    public:
        std::vector<state *> states;
        bool m_running;
    };
}