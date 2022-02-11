#include "player_system.hpp"
#include "../components/player.hpp"
#include "../components/transform.hpp"

namespace brown
{
    void player_system::handle_player_events(char c, WINDOW *win, brain *br)
    {
        for (auto &entity : m_entities)
        {
            auto &pl = br->get_component<player>(entity);
            auto &tr = br->get_component<transform>(entity);

            if (c != ERR)
            {
                switch (c)
                {
                case 'a':
                    tr.position.x--;
                    break;
                case 'd':
                    tr.position.x++;
                    break;
                case 'w':
                    tr.position.y--;
                    break;
                case 's':
                    tr.position.y++;
                    break;
                }
            }
        }
    }
}