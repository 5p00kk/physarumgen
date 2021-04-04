#pragma once

#include "agent_physarum.h"
#include "agent_interface.h"
#include "world_sampler.h"
#include "world.h"
#include <vector>

class c_simulation
{
    public:
        c_simulation(unsigned int m_width, unsigned int m_height);
        bool spawn_world(unsigned int m_width, unsigned int m_height);
        bool spawn_agents(float world_percentage);
        void tick();
    private:
        std::vector<std::unique_ptr<i_agent>> m_agents;
        c_world m_world;
        c_world_sampler m_world_sampler;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
};