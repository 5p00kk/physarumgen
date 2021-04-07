#pragma once

#include "agent_physarum.h"
#include "agent_interface.h"
#include "world_sampler.h"
#include "world.h"
#include "recorder.h"
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
            \brief Set diffusion for the current world.
            \param diff_size Kernel size of diffusion.
        */
        void set_world_diffusion(unsigned int diff_size);
        /*!
            \brief Set decay for the current world.
            \param decay_mult Decay multiplication factor.
            \param decay_sub Decay subtraction factor.
        */
        void set_world_decay(float decay_mult, float decay_sub);
        /*!
            \brief (Re)spawn agents in the world.
            This function removes all old agents and spawns a new group. 
            Agents are randomly sampled from the world grid map.
            \param world_percentage Fraction of the world [0-1] that should be populated by agents.
            \return True if agents were spawned succesfully
            \return False if too many agents were requested
            \return False if there was an attempt to spawn an agent on occupied cell
        */
        bool spawn_agents_uniform(float world_percentage);
        /*!
            \brief (Re)spawn agents in the world.
            This function removes all old agents and spawns a new group. 
            Agents are spawned in a centrally placed square.
            \param square_side Size of the spawn square.
            \return True if agents were spawned succesfully
            \return False if side was larger than world size
        */
        bool spawn_agents_square(unsigned int side);
        /*!
            \brief Progress the world time.
            Movement step for all agents, 
            sensing step for all agents, 
            diffuse the world, 
            decay the world.
        */
        void tick();
        /*!
            \brief Start video/image recording of the current simultation (frames are added on tick)
            \param path Recording path
        */  
        void start_recording(const std::string &path);
    private:
        std::vector<std::unique_ptr<i_agent>> m_agents;    /*!< Vector containing pointers to all agents in the simulation. */
        c_world m_world;                                   /*!< The current world. */
        c_world_sampler m_world_sampler;                   /*!< Object for sampling cells from the current world. */
        c_recorder m_recorder;                             /*!< Object for recording world snapshots. */
        unsigned int m_ticks = 0;                          /*!< Current simulation tick. */
        unsigned int m_width = 0;                          /*!< Current world width */
        unsigned int m_height = 0;                         /*!< Current world height */
};