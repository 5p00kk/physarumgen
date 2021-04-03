#pragma once

#include "utils.h"

class c_agent
{
    public:
        c_agent(unsigned int pos_x, unsigned int pos_y, unsigned int angle);
        void print_info() const;
        s_position m_position;
        unsigned int m_angle;
    private:
};