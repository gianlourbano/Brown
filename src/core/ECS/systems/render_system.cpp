#include "render_system.hpp"
#include "../components/transform.hpp"
#include "../components/animation.hpp"

#include "../../../graphics/window/window.hpp"
#include <dirent.h>
#include <cstring>
#include <unordered_map>

sprite_data GLOBAL_SPRITES_paths{};
std::unordered_map<std::string, sprite_data> GLOBAL_SPRITES{};

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
            if (name.find(".spr") || name.find(".aspr"))
                GLOBAL_SPRITES_paths.push_back(name);
        }
    }
    closedir(dir);

    for (auto &spr : GLOBAL_SPRITES_paths)
    {
        if (spr.find(".spr"))
        {
            sprite_data m_data = brown::load_sprite(spr);
            GLOBAL_SPRITES.insert({spr.substr(0, spr.find(".spr")), m_data});
        }
        else if (spr.find(".aspr"))
        {

        }
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
        graphics::mvwprintvcolors(win, trans.position.y, trans.position.x, true, GLOBAL_SPRITES[spr.sprite_name]);
    }
}

void brown::load_animated_sprite(std::string name) {
    std::string path = "./sprites/";
    std::ifstream asprite_(path.append(name));
    n
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