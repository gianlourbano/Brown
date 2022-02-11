#include "render_system.hpp"
#include "../components/transform.hpp"
#include "../components/animation.hpp"
#include "../../../graphics/window/window.hpp"

void brown::render_system::draw(WINDOW *win, brown::brain *br)
{
    for (auto & entity : m_entities)
    {
        auto &trans = br->get_component<transform>(entity);
        auto &anim = br->get_component<animation>(entity);

        graphics::mvwaddchcolors(win, trans.position.y, trans.position.x, 0, anim.animation_clips[anim.current]);
    }
}