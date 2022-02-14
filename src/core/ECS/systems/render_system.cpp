#include "render_system.hpp"
#include "../components/transform.hpp"
#include "../components/animation.hpp"

#include "../../../graphics/window/window.hpp"
#include <dirent.h>
#include <cstring>

sprite_data GLOBAL_SPRITES_paths{};
std::vector<sprite_data> GLOBAL_SPRITES{};

void brown::render_system::init()
{
    DIR *dir;
    struct dirent *ent;
    ASSERT((dir = opendir("./sprites")) != NULL, "Could not open sprites folder!\n");
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
        {
            std::string name(ent->d_name);
            if (name.find(".spr"))
                GLOBAL_SPRITES_paths.push_back(name);
        }
    }
    closedir(dir);

    for (auto &spr : GLOBAL_SPRITES_paths)
    {
        sprite_data m_data = brown::load_sprite(spr);
        GLOBAL_SPRITES.push_back(m_data);
    }
}

void brown::render_system::draw(WINDOW *win, brown::brain *br)
{
    for (auto &entity : m_entities)
    {
        auto &trans = br->get_component<transform>(entity);
        auto &spr = br->get_component<sprite>(entity);
        auto &anim = br->get_component<animation>(entity);

        // if (anim.clips != 0 && anim.playing)
        //     graphics::mvwprintvcolors(win, trans.position.y, trans.position.x, 0, anim.animation_clips[anim.current].sprite);
        // else
        graphics::mvwprintvcolors(win, trans.position.y, trans.position.x, true, GLOBAL_SPRITES[spr.id]);
    }
}

sprite_data brown::load_sprite(std::string name)
{
    std::string path = "./sprites/";
    std::ifstream sprite_(path.append(name));
    sprite_data m_data;
    std::string line1;

    while (std::getline(sprite_, line1))
    {
        m_data.push_back(line1);
    }

    sprite_.close();
    return m_data;
}