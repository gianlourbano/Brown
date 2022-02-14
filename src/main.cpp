#include "brown.hpp"
#include "core/state/state.hpp"

#include "core/ECS/components/animation.hpp"
#include "core/ECS/components/transform.hpp"
#include "core/ECS/systems/animation_system.hpp"
#include "core/ECS/systems/render_system.hpp"
#include "core/ECS/components/player.hpp"
#include "core/ECS/components/sprite.hpp"
#include "core/ECS/systems/player_system.hpp"

#include "debug/debug_state.hpp"

int frame_passed = 0;
static int FPS = 60;

std::vector<std::string> sprite_1;
std::vector<std::string> room_1;

namespace brown
{
    class state_1 : public state
    {
    public:
        void init(engine *game)
        {
            set_win(brown::graphics::create_newwin(LINES - 2, COLS - 2, 2, 2));
            brown::graphics::start_curses_flags(win);
            game->set_current_screen(win);

            brain.init();

            brain.register_component<animation>();
            brain.register_component<transform>();
            brain.register_component<player>();
            brain.register_component<sprite>();
            animation_system = brain.register_system<brown::animation_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<animation>());
                brain.set_system_signature<brown::animation_system>(signature);
            }

            player_system = brain.register_system<brown::player_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<transform>());
                signature.set(brain.get_component_type<player>());
                brain.set_system_signature<brown::player_system>(signature);
            }

            render_system = brain.register_system<brown::render_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<animation>());
                signature.set(brain.get_component_type<sprite>());
                signature.set(brain.get_component_type<transform>());
                brain.set_system_signature<brown::animation_system>(signature);
            }
            render_system->init();

            room = brain.create_entity();
            m_entities.push_back(room);
            brain.add_component<transform>(room, {0, 0});
            brain.add_component<sprite>(room, {{71, 17}, 0});

            pl = brain.create_entity();
            m_entities.push_back(pl);

            brain.add_component<transform>(pl, {4, 4});
            brain.add_component<player>(pl, {});
            // brain.add_component<animation>(pl, {3, false, 0, true, 20,{'@', '#', 'L'}});

            brain.add_component<sprite>(pl, {{2, 2}, 1});
        };

        void cleanup(){};
        void pause(){};
        void resume(){};

        void handle_events(engine *game)
        {
            int ch = wgetch(win);
            if (ch != ERR)
            {
                switch (ch)
                {
                case 'p':
                    game->quit();
                    break;
                case 'h':
                    animation_system->play(m_entities[0], &brain);
                    break;

                case 'j':
                    animation_system->stop(m_entities[0], &brain);
                    break;
                case KEY_F(1):
                    game->push_state(brown::debug::debug_state::instance());
                    break;
                }
            }

            player_system->handle_player_events(ch, win, &brain);
        };

        void update(engine *game)
        {
            frame_passed++;
            animation_system->update(&brain, frame_passed);
            if (frame_passed > FPS)
                frame_passed = 0;
        };

        void draw(engine *game)
        {
            werase(win);
            box(win, 0, 0);

            render_system->draw(win, &brain);
        };

        static state_1 *instance()
        {
            return &m_state_1;
        }

    protected:
        state_1() {}

    private:
        static state_1 m_state_1;
        std::vector<entity> m_entities;

        std::shared_ptr<brown::animation_system> animation_system;
        std::shared_ptr<brown::render_system> render_system;
        std::shared_ptr<brown::player_system> player_system;

        entity pl;
        entity room;
    };
}

brown::state_1 brown::state_1::m_state_1;

class game : public brown::engine
{
public:
    void init(int width, int height)
    {
        brown::engine::init(width, height);
        brown::colors::init_color_from_rgb(9, 43, 43, 43);
        brown::colors::init_color_from_rgb(10, 66, 62, 63);
        brown::colors::init_color_from_rgb(11, 23, 16, 16);

        brown::colors::init_color_from_rgb(12, 255, 229, 5);
        brown::colors::init_color_from_rgb(13, 255, 251, 5);

        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_BLUE, COLOR_BLUE);
        init_pair(2, COLOR_CYAN, COLOR_CYAN);
        init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(4, 11, 11);
        init_pair(5, 9, 9);
        init_pair(6, 10, 10);
        init_pair(7, 12, 12);
        init_pair(8, 13, 13);
        init_pair(9, COLOR_WHITE, 10);
    }
};

int main()
{
    game engine;

    engine.init(640, 480);

    engine.change_state(brown::state_1::instance());

    while (engine.running())
    {
        if (usleep(1000000 / FPS) == EINTR)
            break;

        engine.handle_events();
        engine.update();
        engine.draw();
    }

    endwin();

    return 0;
}