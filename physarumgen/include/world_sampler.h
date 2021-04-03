#pragma once

#include "utils.h"
#include <vector>

class c_world_sampler
{
    public:
        c_world_sampler(unsigned int width, unsigned int height);
        void reset_range(unsigned int width, unsigned int height);
        s_position get_next_position();
    private:
        std::vector<unsigned int> m_positions;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_current_idx;
};