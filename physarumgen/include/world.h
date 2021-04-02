#pragma once

#include "agent.h"
#include <vector>

class c_world
{
    public:
        c_world(unsigned int height, unsigned int width);
        void spawn_agents(float world_percentage);
    private:
        std::vector<c_agent> m_agents;
        unsigned int m_height;
        unsigned int m_width;
};