#include "brown.hpp"

int frame_passed = 0;
static int FPS = 60;

namespace brown
{
    size_t KEY_PRESSED;
}

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
            brain.register_component<sprite>();
            brain.register_component<rigid_body>();
            brain.register_component<force>();
            brain.register_component<native_script>();
            animation_system = brain.register_system<brown::animation_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<animation>());
                brain.set_system_signature<brown::animation_system>(signature);
            }

            scripts_system = brain.register_system<brown::scripts_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<native_script>());
                brain.set_system_signature<brown::scripts_system>(signature);
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

            physics_system = brain.register_system<brown::physics_system>();
            {
                signature signature;
                signature.set(brain.get_component_type<rigid_body>());
                signature.set(brain.get_component_type<force>());
                signature.set(brain.get_component_type<transform>());
                brain.set_system_signature<brown::physics_system>(signature);
            }

            auto room = create_entity("room");
            room.add_component<transform>({{0, 0}, 0});
            room.add_component<sprite>({{71, 17}, "room1"});
            room.add_component<animation>({3, false, 0, false, 20, {0, 0}, "animated_room", true});

            auto pl = create_entity("player");

            class player_controller : public scriptable_entity
            {
            public:
                void on_create()
                {
                    health = 100;
                    ts = &get_component<transform>();
                }

                void on_update()
                {
                    if (brown::KEY_PRESSED == 'a')
                        ts->position.x--;
                    else if (brown::KEY_PRESSED == 'd')
                        ts->position.x++;

                    if (brown::KEY_PRESSED == 'w')
                        ts->position.y--;
                    else if (brown::KEY_PRESSED == 's')
                        ts->position.y++;
                    
                    if (brown::KEY_PRESSED == 't')
                        m_entity.delete_entity();
                }

            private:
                transform *ts = nullptr;
                int health;
            };

            pl.add_component<transform>({{4, 4}, 1});
            pl.add_component<sprite>({{2, 2}, "sprite2"});
            pl.add_component<animation>({5, false, 0, false, 10, {2, 2}, "animated1"});
            pl.add_component<native_script>({}).bind<player_controller>();
        };

        void cleanup(){};
        void pause(){};
        void resume(){};

        void handle_events(engine *game)
        {
            brown::KEY_PRESSED = wgetch(win);
            if (brown::KEY_PRESSED != ERR)
            {
                switch (brown::KEY_PRESSED)
                {
                case 'p':
                    game->quit();
                    break;
                case 'h':
                    animation_system->play(find_entity_id("player"), &brain);
                    break;
                case 'j':
                    animation_system->stop(find_entity_id("player"), &brain);
                    break;
                case 'u':
                    animation_system->play(find_entity_id("room"), &brain);
                    break;
                case 'y':
                    break;
                case KEY_F(1):
                    game->push_state(brown::debug::debug_state::instance());
                    break;
                }
            }

            physics_system->handle_events(&brain);
        };

        void update(engine *game)
        {
            frame_passed++;
            animation_system->update(&brain, frame_passed);
            if (frame_passed > FPS)
                frame_passed = 0;
            physics_system->update(&brain);
            scripts_system->update(&brain);
        };

        void draw(engine *game)
        {
            werase(win);
            werase(game->get_std_screen());
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
        std::shared_ptr<brown::animation_system> animation_system;
        std::shared_ptr<brown::render_system> render_system;
        std::shared_ptr<brown::physics_system> physics_system;
        std::shared_ptr<brown::scripts_system> scripts_system;
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
        brown::colors::init_color_from_rgb(14, 60, 217, 19);
        brown::colors::init_color_from_rgb(15, 222, 184, 135);
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
        init_pair(10, 14, 14);
        init_pair(11, 15, 15);
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