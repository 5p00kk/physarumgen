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
        /*!
            \brief Constructor
            \param pos_x Initial x position of the agent.
            \param pos_y Initial y position of the agent.
            \param alpha Initial direction of the agent.
            \param world Pointer to the c_world object in which the agent is spawned.
        */
        c_physarum(float pos_x, float pos_y, float alpha, c_world *world);
        /*!
        \brief Print agent information
        */
        void print_info() const override;
        /*!
        \brief Move the agent to the new position.

        The agent attempts to move forward by <step_size>.
        If the movement is not allowed, the agent will randomly sample new orientation.
        If the movement is allowed, after moving the agent will deposit <deposition_value> to trail track.
        */
        void movement_step() override;
        /*!
        \brief Sense the environment.

        The agent will sense three points around it (left, center, right).
        The location of sensors is determined by <sensor_angle> and <sensor_offset>.
        Depending on sensed trail values, the agent will choose new orientation based on <rotation_angle>
        For more details on new orientation see Jone's paper.
        */
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