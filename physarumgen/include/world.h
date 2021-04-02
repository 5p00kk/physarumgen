#pragma once

#include "agent.h"
#include <vector>
#include <opencv2/highgui.hpp>

class c_world
{
    public:
        c_world(unsigned int height, unsigned int width);
        bool spawn_agents(float world_percentage);
    private:
        std::vector<c_agent> m_agents;
        unsigned int m_height;
        unsigned int m_width;
        cv::Mat m_world_grid;
};