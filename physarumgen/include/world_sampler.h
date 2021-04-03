#pragma once

#include "utils.h"
#include <vector>
#include <random>

class c_world_sampler
{
    public:
        c_world_sampler(unsigned int width, unsigned int height);
        void reset_range(unsigned int width, unsigned int height);
        s_ui_vec2 get_next_position();
        float get_angle();
    private:
        std::vector<unsigned int> m_positions;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_current_idx;
        /* Random number generator for direction */
        std::random_device m_dev;
        std::mt19937 m_rng;
        std::uniform_int_distribution<std::mt19937::result_type> m_dist360;
};