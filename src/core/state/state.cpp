#include "state.hpp"

namespace brown {
    entity state::create_entity(std::string name) {
        entity e = brain.create_entity();
        m_entities.insert({name, e});
        return e;
    }

    entity state::find_entity(std::string name) {
        return m_entities[name];
    }
}