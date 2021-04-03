#include "world_sampler.h"
#include <algorithm>
#include <iostream>

c_world_sampler::c_world_sampler(unsigned int width, unsigned int height)
: m_width{width}
, m_height{height}
, m_current_idx{}
, m_rng{m_dev()}
, m_dist360{0, 359}
{
    reset_range(m_width, m_height);
}

void c_world_sampler::reset_range(unsigned int width, unsigned int height)
{
    unsigned int num_elements = width*height;

    m_positions.clear();
    m_positions.reserve(num_elements);
    for(int i=0;i<num_elements;i++)
    {
        m_positions.push_back(i);
    }
    std::random_shuffle(m_positions.begin(), m_positions.end());

    m_current_idx = 0;
}

s_vec2 c_world_sampler::get_next_position()
{
    s_vec2 ret_val{0,0};

    if(m_current_idx >= m_positions.size())
    {
        std::cout << "<c_world_sampler::get_next_position()> ERROR: Already sampled all" << std::endl;
    }
    else
    {
        unsigned int position = m_positions[m_current_idx];
        ret_val.x = position%m_width;
        ret_val.y = position/m_width;
        m_current_idx++;
    }

    return ret_val;
}

float c_world_sampler::get_angle()
{
    return (float)m_dist360(m_rng);
}
