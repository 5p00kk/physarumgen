#include "world.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <math.h>

c_world::c_world(unsigned int width, unsigned int height)
: m_width{width}
, m_height{height}
, m_world_grid{height, width, CV_8UC1}
, m_trail_grid{height, width, CV_8UC1}
, m_world_sampler{width, height}
{
    cv::namedWindow("world");
    cv::moveWindow("world", 500,300);
    cv::namedWindow("trail");
    cv::moveWindow("trail", m_width + 500,300);
}

bool c_world::spawn_agents(float world_percentage)
{
    /* Calculate how many agents are requested */
    unsigned int world_area = m_width * m_height;
    unsigned int num_agents = (unsigned int)(world_percentage * world_area);

    /* Make sure that there are not too many agents requested */
    if(num_agents >= world_area)
    {
        std::cout << "<c_world::spawn_agents>: Could not spawn agents" << std::endl;
        return false;
    }

    /* (Re)spawn agents */
    m_agents.clear();
    m_agents.reserve(num_agents);
    for(int i=0; i<num_agents; i++)
    {
        s_ui_vec2 tmp_pos = m_world_sampler.get_next_position();
        m_agents.emplace_back((float)tmp_pos.x, (float)tmp_pos.y, m_world_sampler.get_angle());
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    update_world();

    return true;
}

void c_world::movement_step()
{
    /* Shuffle agent to avoid emergent patterns due to move sequence */
    /* TODO - this is slow, potential optimization */
    std::random_shuffle(m_agents.begin(), m_agents.end());

    for(auto &agent : m_agents) 
    {
        /* Calculate where the agents wants to go */
        float new_x = agent.m_pose.x + agent.m_step_size * std::cos(agent.m_pose.alpha*PI/180.0);
        float new_y = agent.m_pose.y + agent.m_step_size * std::sin(agent.m_pose.alpha*PI/180.0);

        /* Get grid coordinates */
        /* TODO: paper says they just cast rounding maybe maybe do some interpolation here */
        int grid_old_x = to_grid(agent.m_pose.x);
        int grid_old_y = to_grid(agent.m_pose.y);
        int grid_new_x = to_grid(new_x);
        int grid_new_y = to_grid(new_y);

        if(grid_new_x == grid_old_x && grid_new_y == grid_old_y)
        {
            /* Agent does not move enough to occupy a new grid cell */
            /* Only update agent state */
            agent.m_pose.x = new_x;
            agent.m_pose.y = new_y;
        }
        else
        {
            /* Agent wants to move to new grid cell */

            /* Check if out of bounds */
            bool in_bounds = (grid_new_x >= 0) && (grid_new_x < m_width);
            in_bounds &= (grid_new_y >= 0) && (grid_new_y < m_height);

            /* Check if space is free */
            bool space_free = (m_world_grid.at<uchar>(grid_new_y, grid_new_x, 0) == 0);

            if(in_bounds && space_free)
            {
                /* Move in grid cell */
                m_world_grid.at<uchar>(grid_old_y, grid_old_x, 0) = 0;
                m_world_grid.at<uchar>(grid_new_y, grid_new_x, 0) = 255;

                /* Update agent state */
                agent.m_pose.x = new_x;
                agent.m_pose.y = new_y;

                /* Deposit trail in the new location */
                /* TODO: better saturation */
                uchar trail_value = m_trail_grid.at<uchar>(grid_new_y, grid_new_x, 0);
                if(trail_value <= (255 - agent.m_deposition_value))
                {
                    m_trail_grid.at<uchar>(grid_new_y, grid_new_x, 0) = trail_value + agent.m_deposition_value;
                }
            }
            else
            {
                /* Dont move but change angle */
                agent.m_pose.alpha = m_world_sampler.get_angle();
            }
        }
    }    
}

void c_world::sensory_step()
{
    for(auto &agent : m_agents) 
    {
        /* TODO: a lot of this could be done insisde of the agent */
        /* TODO: split into smaller functions */

        /******************************/
        /* Calculate sensor positions */
        /******************************/
        s_f_vec2 sensor_center = dest_position(agent.m_pose.x, agent.m_pose.y, agent.m_pose.alpha, agent.m_sensor_offset);
        s_f_vec2 sensor_left   = dest_position(agent.m_pose.x, agent.m_pose.y, agent.m_pose.alpha-agent.m_sensor_angle, agent.m_sensor_offset);
        s_f_vec2 sensor_right  = dest_position(agent.m_pose.x, agent.m_pose.y, agent.m_pose.alpha+agent.m_sensor_angle, agent.m_sensor_offset);

        
        /******************************/
        /* Sample sensor readings     */
        /******************************/
        s_ui_vec2 grid_sensor_left{to_grid(sensor_left.x), to_grid(sensor_left.y)};
        s_ui_vec2 grid_sensor_right{to_grid(sensor_right.x), to_grid(sensor_right.y)};;
        s_ui_vec2 grid_sensor_center{to_grid(sensor_center.x), to_grid(sensor_center.y)};;
        uchar reading_left = 0;
        uchar reading_right = 0;
        uchar reading_center = 0;
       
        if(check_inbounds(grid_sensor_left.x, grid_sensor_left.y))
        {
            reading_left = m_trail_grid.at<uchar>(to_grid(sensor_left.y), to_grid(sensor_left.x), 0);
        }
        if(check_inbounds(grid_sensor_right.x, grid_sensor_right.y))
        {
            reading_right = m_trail_grid.at<uchar>(to_grid(sensor_right.y), to_grid(sensor_right.x), 0);
        }
        if(check_inbounds(grid_sensor_center.x, grid_sensor_center.y))
        {
            reading_center = m_trail_grid.at<uchar>(to_grid(sensor_center.y), to_grid(sensor_center.x), 0);
        }


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
            agent.m_pose.alpha += direction * agent.m_rotation_angle;
        }
        else if(reading_left < reading_right)
        {
            agent.m_pose.alpha += agent.m_rotation_angle;
        }
        else if(reading_right < reading_left)
        {
            agent.m_pose.alpha -= agent.m_rotation_angle;
        }
        else
        {
            /* Do nuthin */
        }
    }
}

void c_world::update_world()
{
    m_world_grid = cv::Scalar::all(0);
    
    for(auto &agent : m_agents) 
    {
        m_world_grid.at<uchar>(agent.m_pose.y, agent.m_pose.x, 0) = 255;
    }
}

bool c_world::check_inbounds(unsigned int x, unsigned int y) const
{
    return((x >= 0) && (x < m_width) && (y >= 0) && (y < m_height));
}

void c_world::display(int delay) const
{
    cv::imshow("world", m_world_grid);
    cv::imshow("trail", m_trail_grid);
    cv::waitKey(delay);
}