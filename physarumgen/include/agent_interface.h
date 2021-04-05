#pragma once

#include "world.h"
#include "utils.h"

/*!
    \brief Agent's 2D pose: position (x,y) and orientation (alpha).
*/
struct s_agent_pose
{
    s_f_vec2 position; /*!< Agent's 2D position */
    float alpha;       /*!< Agent's orientation */
};

/*! 
    \brief Abstract class for agents.

    The interface requires implemnentations to provide methods for agent's
    movement and sensing.
*/
class i_agent
{
    public:
        /*!
            \brief Constructor
            \param pos_x Initial x position of the agent.
            \param pos_y Initial y position of the agent.
            \param alpha Initial direction of the agent.
            \param world Pointer to the c_world object in which the agent is spawned.
        */
        i_agent(float pos_x, float pos_y, float alpha, c_world *world);

        /*!
        \brief Print agent information
        */
        virtual void print_info() const = 0;

        /*!
        \brief Move the agent to the new position.
        */
        virtual void movement_step() = 0;

        /*!
        \brief Sense the world.
        */
        virtual void sensing_step() = 0;
    protected:

        /*!
            \brief Current pose (position, orientation) of the agent.
        */
        s_agent_pose m_pose;

        /*!
            \brief Pointer to the world in which the agent lives.
        */
        c_world *m_world;
};