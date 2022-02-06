#pragma once
#include "../types.hpp"
#include <set>

namespace brown
{
    class system
    {
    public:
        std::set<entity> m_entities;
    };
}