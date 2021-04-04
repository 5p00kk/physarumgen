#pragma once

#include "agent_interface.h"

struct s_physarum_params
{
    float sensor_angle = 45.0f;
    float sensor_offset = 9.0f;
    float rotation_angle = 45.0f;
    float step_size = 1.0f;
    unsigned int deposition_value = 5;
}

class c_physarum: public i_agent
{
    public:
        c_physarum(float pos_x, float pos_y, float alpha, c_world *world);
        void print_info() const override;
        void movement_step() override;
        void sensing_step() override;
    private:
        s_f_vec2 calc_destination(const s_f_vec2 &start_pt, float angle, float distance);
        s_physarum_params m_params;
};