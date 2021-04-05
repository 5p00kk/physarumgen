#pragma once

#include "agent_interface.h"

/*! 
    \brief Parameters defining Physarum agent.
*/
struct s_physarum_params
{
    float sensor_angle = 45.0f;       /*!< Angle of the left and right sensors from the center */
    float sensor_offset = 9.0f;       /*!< How far from the agent the sensor is located */
    float rotation_angle = 45.0f;     /*!< How much does the agent rotate on orientation change */
    float step_size = 1.0f;           /*!< Agent's forward step size */
    unsigned int deposition_value = 5;    /*!< How much trail is being depoited at once */
};

/*! 
    \brief Physarum agent implementation.

    This class implementes an agent based on Jone's paper.
*/
class c_physarum: public i_agent
{
    public:
        c_physarum(float pos_x, float pos_y, float alpha, c_world *world);
        void print_info() const override;
        void movement_step() override;
        void sensing_step() override;
    private:
        /*!
            \brief Based on starting point, angle and distance, calculate the end point.
            \param start_pt Starting 2D point.
            \param angle Direction of the movement.
            \param distance Distance covered.
            \returns 2D end point
        */
        s_f_vec2 calc_destination(const s_f_vec2 &start_pt, float angle, float distance);

        /*!
            \brief Physarum agent parameters.
        */
        s_physarum_params m_params;
};