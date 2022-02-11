#include "state.hpp"

namespace brown {
    entity state::create_entity() {
        m_entities.push_back(brain.create_entity());
        return m_entities.back();
    }
}