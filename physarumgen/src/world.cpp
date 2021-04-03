#include "world.h"
#include <iostream>

c_world::c_world(unsigned int width, unsigned int height)
: m_width{width}
, m_height{height}
, m_world_grid{height, width, CV_8UC1}
, m_world_sampler{width, height}
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
        s_vec2 tmp_pos = m_world_sampler.get_next_position();
        m_agents.emplace_back(tmp_pos.x, tmp_pos.y, m_world_sampler.get_angle());
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    return true;
}

void c_world::update_world()
{
    m_world_grid = cv::Scalar::all(0);
    
    for(auto &agent : m_agents) 
    {
        m_world_grid.at<uchar>(agent.m_pose.y, agent.m_pose.x, 0) = 255;
    }
}