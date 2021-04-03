#include "agent.h"
#include <iostream>

c_agent::c_agent(float pos_x, float pos_y, float alpha)
    : m_pose{pos_x, pos_y, alpha}
{
    std::cout << "Created c_agent using user values" << std::endl;
}

void c_agent::print_info() const
{
    std::cout << std::endl << "Printing c_agent info" << std::endl;
    std::cout << "x: " << m_pose.x << std::endl;
    std::cout << "y: " << m_pose.y << std::endl;
    std::cout << "a: " << m_pose.alpha << std::endl << std::endl;
}