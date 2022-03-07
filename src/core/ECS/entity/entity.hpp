#pragma once
#include "core/types.hpp"
#include "core/brain.hpp"
#include <typeinfo>

namespace brown
{
    class entity
    {
    public:
        entity(){};
        entity(entity_id id, brain *br, int z_index) : m_entity_id(id), m_brain(br), z_index(z_index){};
        entity(const entity &) = default;

        template <typename T>
        T& add_component(T component)
        {
            m_brain->add_component<T>(m_entity_id, std::forward<T>(component));
            return m_brain->get_component<T>(m_entity_id);
        }

        template <typename T>
        void remove_component() {}

        entity_id get_id() { return m_entity_id; }

        friend class state;

    
        template <typename T>
        T& get_component() { return m_brain->get_component<T>(m_entity_id); }

    private:
        entity_id m_entity_id;
        brain *m_brain;
        int z_index;
    };

    class scriptable_entity
    {
    public:
        virtual ~scriptable_entity() {}

        template <typename T>
        T &get_component() { return m_entity.get_component<T>(); }

    protected:
        virtual void on_create() {}
        virtual void on_destroy() {}
        virtual void on_update() {}
    private:
        entity m_entity;
        friend class scene;
        friend class scripts_system;
    };

}