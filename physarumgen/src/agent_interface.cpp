#include "agent_interface.h"
#include <iostream>

i_agent::i_agent(float pos_x, float pos_y, float alpha, c_world *world)
    : m_pose{{pos_x, pos_y}, alpha}
    , m_world{world}
{}