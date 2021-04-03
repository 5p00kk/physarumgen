#pragma once

struct s_agent_pose
{
    float x;
    float y;
    float alpha;
};

class c_agent
{
    public:
        c_agent(float pos_x, float pos_y, float alpha);
        void print_info() const;
        s_agent_pose m_pose;
        float m_sensor_angle = 45.0f;
        float m_rotation_angle = 45.0f;
        unsigned int m_deposition_value = 5;
    private:
};