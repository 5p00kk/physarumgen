#pragma once

#include "agent_physarum.h"
#include "agent_interface.h"
#include "world_sampler.h"
#include "world.h"
#include <vector>

/*! 
    \brief Main simulation wrapper class. 

    This class contains the world and agents and allows to progress simulation time.
*/
class c_simulation
{
    public:
        /*!
            \brief Constructor
            \param width Width of the world.
            \param height Height of the world.
        */
        c_simulation(unsigned int width, unsigned int height);
        /*!
            \brief (Re)spawn a world.
            This function will clear all agent's of the current world and spawn a new empty world.
            \param width Width of the new world.
            \param height Height of the new world.
        */
        void spawn_world(unsigned int width, unsigned int height);
        /*!
            \brief (Re)spawn agents in the world.
            This function removes all old agents and spawns a new group. 
            \param world_percentage Fraction of the world [0-1] that should be populated by agents.
            \return True if agents were spawned succesfully
            \return False if too many agents were requested
            \return False if there was an attempt to spawn an agent on occupied cell
        */
        bool spawn_agents(float world_percentage);
        /*!
            \brief Progress the world time.
            Movement step for all agents, 
            sensing step for all agents, 
            diffuse the world, 
            decay the world.
        */
        void tick();
    private:
        std::vector<std::unique_ptr<i_agent>> m_agents;    /*!< Vector containing pointers to all agents in the simulation. */
        c_world m_world;                                   /*!< The current world. */
        c_world_sampler m_world_sampler;                   /*!< Object for sampling cells from the current world. */
        unsigned int m_width = 0;                          /*!< Current world width */
        unsigned int m_height = 0;                         /*!< Current world height */
};