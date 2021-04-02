#include "world.h"
#include <iostream>

c_world::c_world(unsigned int height, unsigned int width)
: m_height{height}
, m_width{width}
{}

bool c_world::spawn_agents(float world_percentage)
{
    /* Calculate how many agents are requested */
    unsigned int world_area = m_width * m_height;
    unsigned int num_agents = (unsigned int)(world_percentage * world_area);

    /* Make sure that there are not too many agents requested */
    if(num_agents >= world_area)
    {
        std::cout << "<c_world::spawn_agents>: Could not spawn agents" << std::endl;
        return false;
    }

    /* (Re)spawn agents */
    m_agents.clear();
    m_agents.reserve(num_agents);
    for(int i=0; i<num_agents; i++)
    {
        m_agents.emplace_back();
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    return true;
}