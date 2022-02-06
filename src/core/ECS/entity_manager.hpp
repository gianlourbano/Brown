#include "../types.hpp"
#include "../../debug/debugger.hpp"
#include <array>
#include <queue>

namespace brown
{
    class entity_manager
    {
    public:
        entity_manager()
        {
            for (entity entity = 0; entity < MAX_ENTITIES; ++entity)
                m_avaliable_entities.push(entity);
        }

        entity create_entity()
        {
            entity id = m_avaliable_entities.front();
            m_avaliable_entities.pop();
            ++m_entity_count;
            return id;
        }

        void destroy_entity(entity entity)
        {

            m_signatures[entity].reset();
            m_avaliable_entities.push(entity);
            --m_entity_count;
        }

        void set_signature(entity entity, signature signature)
        {

            m_signatures[entity] = signature;
        }

        signature get_signature(entity entity)
        {
            return m_signatures[entity];
        }

        private:
            std::queue<entity> m_avaliable_entities{};
            std::array<signature, MAX_ENTITIES> m_signatures{};
            entity m_entity_count;
    };
}