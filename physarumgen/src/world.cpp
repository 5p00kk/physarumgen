#include "world.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <math.h>

c_world::c_world(unsigned int width, unsigned int height)
: m_width{width}
, m_height{height}
, m_world_grid{height, width, CV_8UC1}
, m_trail_grid{height, width, CV_8UC1}
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
        m_agents.emplace_back((float)tmp_pos.x, (float)tmp_pos.y, m_world_sampler.get_angle());
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    update_world();

    return true;
}

void c_world::move_agents()
{
    /* Shuffle agent to avoid emergent patterns due to move sequence */
    /* TODO - this is slow, potential optimization */
    std::random_shuffle(m_agents.begin(), m_agents.end());

    for(auto &agent : m_agents) 
    {
        /* Calculate where the agents wants to go */
        float next_x = agent.m_pose.x + agent.m_step_size * std::cos(agent.m_pose.alpha*PI/180.0);
        float next_y = agent.m_pose.y + agent.m_step_size * std::sin(agent.m_pose.alpha*PI/180.0);

        /* Cast it into the grid */
        /* TODO: paper says they jsut cast it maybe maybe do some interpolation here */
        int grid_next_x = (int)next_x;
        int grid_next_y = (int)next_y;

        /* Check if out of bounds */
        bool in_bounds = (grid_next_x >= 0) && (grid_next_x < m_width);
        in_bounds &= (grid_next_y >= 0) && (grid_next_y < m_height);

        /* Check if space is free */
        bool space_free = (m_world_grid.at<uchar>grid_next_y, grid_next_x, 0) == 0);

        if(in_bounds && space_free)
        {
            /* Move */
            m_world_grid.at<uchar>((int)agent.m_pose.y, (int)agent.m_pose.x, 0) = 0;
            agent.m_pose.x = next_x;
            agent.m_pose.y = next_y;
            m_world_grid.at<uchar>((int)agent.m_pose.y, (int)agent.m_pose.x, 0) = 255;
        }
        else
        {
            /* Dont move but change angle */
            agent.m_pose.alpha = m_world_sampler.get_angle();
        }
    }    
}

void c_world::update_world()
{
    m_world_grid = cv::Scalar::all(0);
    
    for(auto &agent : m_agents) 
    {
        m_world_grid.at<uchar>(agent.m_pose.y, agent.m_pose.x, 0) = 255;
    }
}

void c_world::display() const
{
    cv::imshow("world", m_world_grid);
    cv::waitKey(100);
}