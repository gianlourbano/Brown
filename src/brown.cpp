#include "brown.hpp"
#include "core/state/state.hpp"

namespace brown
{
    void engine::init(int width = 640, int height = 480)
    {

        //setlocale(LC_ALL, "");
        stdscreen = initscr();    /* Start curses mode 		*/
        colors::start_colors();           // starts color mode -from colors.hpp
        noecho();                 // prevents user-inputted charters to be displayed on the stdscreen
        nodelay(stdscreen, true); // makes getch non-blocking
        raw();                    // ncurses will report any keystrokes with getch immediately
        curs_set(0);              // hide the cursor by default
        keypad(stdscreen, true);

        m_running = true;

        wrefresh(stdscreen);
    }

    void engine::quit()
    {
        this->m_running = false;
    }

    void engine::handle_events()
    {
        states.back()->handle_events(this);
    }

    void engine::update()
    {

        states.back()->update(this);
    }

    void engine::draw()
    {
        states.back()->draw(this);
    }

    void engine::change_state(state *state)
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        states.push_back(state);
        states.back()->init(this);
    }

    void engine::push_state(state *state)
    {
        if (!states.empty())
        {
            states.back()->pause();
        }

        states.push_back(state);
        states.back()->init(this);
    }

    void engine::pop_state()
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        if (!states.empty())
        {
            states.back()->resume();
        }
    }
}
