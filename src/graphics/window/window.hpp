#pragma once
#include <ncurses.h>

namespace brown::graphics {
    WINDOW *create_newwin(int height, int width, int starty, int startx);
    void destroy_win(WINDOW *local_win);
    void mvwprintwcolors(WINDOW *win, int y, int x, int pair, const char *s, ...);
    void mvwaddchcolors(WINDOW *win, int y, int x, int pair, char c);
}