#pragma once

#include "utils.h"

class c_agent
{
    public:
        c_agent(unsigned int pos_x, unsigned int pos_y, float angle);
        void print_info() const;
        s_position query_move() const;
        void move();
        s_position m_position;
        float m_angle;
    private:
};