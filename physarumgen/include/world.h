#pragma once

#include "agent.h"
#include "world_sampler.h"
#include <vector>
#include <opencv2/highgui.hpp>

class c_world
{
    public:
        c_world(unsigned int width, unsigned int height);
        bool spawn_agents(float world_percentage);
        void update_world();
    private:
        std::vector<c_agent> m_agents;
        unsigned int m_width;
        unsigned int m_height;
        cv::Mat m_world_grid;
        c_world_sampler m_world_sampler;
};