#pragma once

#include "utils.h"
#include <vector>

/*!
    \brief Class for sampling cells from the world grid. 
    It is ensured that each cell can be sampled only once.
*/
class c_world_sampler
{
    public:
        /*!
            \brief Constructor.
            \param width Width of the world to sample from
            \param height Height of the world to sample from
        */
        c_world_sampler(unsigned int width, unsigned int height);
        /*!
            \brief Reset the sampler.
            \param width Width of the world to sample from
            \param height Height of the world to sample from
        */
        void reset_range(unsigned int width, unsigned int height);
        /*!
            \brief Sample next cell from the world.
            \return Randomly sampled cell from the world.
            \return {0, 0} cell if all cells have been sampled already (and printout error message).
        */
        s_ui_vec2 get_next_position();
    private:
        std::vector<unsigned int> m_positions;   /*!< Internal positions vector for sampling */
        unsigned int m_width;                    /*!< Width of the world to sample from */
        unsigned int m_height;                   /*!< Height of the world to sample from */
        unsigned int m_current_idx;              /*!< Index of currently sampled cell */
};