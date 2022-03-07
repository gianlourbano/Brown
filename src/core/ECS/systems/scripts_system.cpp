#include "scripts_system.hpp"

namespace brown
{
    void scripts_system::update(brain *br)
    {
        for (auto &e : m_entities)
        {
            auto &script = br->get_component<native_script>(e);

            if(!script.instance) {
                script.instance = script.instantiate_script();
                script.instance->m_entity = entity{e, br, 0};

            }
            script.instance->on_update();
        }
    }
}