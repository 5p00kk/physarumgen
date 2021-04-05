#include "agent_physarum.h"
#include "utils.h"
#include <iostream>

c_physarum::c_physarum(float pos_x, float pos_y, float alpha, c_world *world)
    : i_agent{pos_x, pos_y, alpha, world}
{}

void c_physarum::print_info() const
{
    std::cout << std::endl << "Printing c_physarum info" << std::endl;
    std::cout << "x: " << m_pose.position.x << std::endl;
    std::cout << "y: " << m_pose.position.y << std::endl;
    std::cout << "a: " << m_pose.alpha << std::endl << std::endl;
}


void c_physarum::movement_step()
{
    /* Calculate where the agent wants to go */
    s_f_vec2 desitnation = calc_destination(m_pose.position, m_pose.alpha, m_params.step_size);
    
    if(m_world->same_cell(m_pose.position, desitnation))
    {
        m_pose.position.x = desitnation.x;
        m_pose.position.y = desitnation.y;
    }
    else if(m_world->move_agent(m_pose.position, desitnation))
    {
        m_pose.position.x = desitnation.x;
        m_pose.position.y = desitnation.y;
        m_world->deposit_trail(m_pose.position, m_params.deposition_value);
    }
    else
    {
        m_pose.alpha = random_angle();
    }
}


void c_physarum::sensing_step()
{
    /******************************/
    /* Calculate sensor positions */
    /******************************/
    s_f_vec2 sensor_center = calc_destination(m_pose.position, m_pose.alpha,                       m_params.sensor_offset);
    s_f_vec2 sensor_left   = calc_destination(m_pose.position, m_pose.alpha-m_params.sensor_angle, m_params.sensor_offset);
    s_f_vec2 sensor_right  = calc_destination(m_pose.position, m_pose.alpha+m_params.sensor_angle, m_params.sensor_offset);

    /******************************/
    /* Sample sensor readings     */
    /******************************/
    uchar reading_left = m_world->sense_world(sensor_left);
    uchar reading_right = m_world->sense_world(sensor_right);
    uchar reading_center = m_world->sense_world(sensor_center);

    /******************************/
    /* Adjust agent's direction   */
    /******************************/
    if(reading_center > reading_left && reading_center > reading_right)
    {
        /* Do nuthin */
    }
    else if(reading_center < reading_left && reading_center < reading_right)
    {
        int direction = random_bool() ? 1 : -1;
        m_pose.alpha += direction * m_params.rotation_angle;
    }
    else if(reading_left < reading_right)
    {
        m_pose.alpha += m_params.rotation_angle;
    }
    else if(reading_right < reading_left)
    {
        m_pose.alpha -= m_params.rotation_angle;
    }
    else
    {
        /* Do nuthin */
    }
}


s_f_vec2 c_physarum::calc_destination(const s_f_vec2 &start_pt, float angle, float distance)
{
    s_f_vec2 ret_val{start_pt.x + distance * std::cos((angle)*PI/180.0f), 
                     start_pt.y + distance * std::sin((angle)*PI/180.0f)};
    return ret_val;
}