#pragma once

#include "world.h"
#include "utils.h"

struct s_agent_pose
{
    s_f_vec2 position;
    float alpha;
};

class i_agent
{
    public:
        i_agent(float pos_x, float pos_y, float alpha, c_world *world);
        virtual void print_info() const = 0;
        virtual void movement_step() = 0;
        virtual void sensing_step() = 0;
    private:
        s_agent_pose m_pose;
        c_world *m_world;
};