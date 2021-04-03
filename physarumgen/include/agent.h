#pragma once

#include "utils.h"

class c_agent
{
    public:
        c_agent(unsigned int pos_x, unsigned int pos_y, float alpha);
        void print_info() const;
        s_position m_position;
        float m_alpha;
        float m_sensor_angle = 45.0f;
        float m_rotation_angle = 45.0f;
        unsigned int m_deposition_value = 5;
    private:
};