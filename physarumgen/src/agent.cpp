#include "agent.h"
#include <iostream>

c_agent::c_agent(unsigned int pos_x, unsigned int pos_y, float angle)
    : m_position{pos_x, pos_y}
    , m_angle{angle}
{
    std::cout << "Created c_agent using user values" << std::endl;
}

void c_agent::print_info() const
{
    std::cout << std::endl << "Printing c_agent info" << std::endl;
    std::cout << "x: " << m_position.x << std::endl;
    std::cout << "y: " << m_position.y << std::endl;
    std::cout << "a: " << m_angle << std::endl << std::endl;
}