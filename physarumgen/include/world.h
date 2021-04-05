#pragma once

#include "utils.h"
#include <opencv2/highgui.hpp>

/*!
    \brief Class containing world information. Including world (agent) gridmap and trail map.
*/
class c_world
{
    public:
        /*!
            \brief Constructor.
            \param width Width of the world.
            \param height Height of the world.
            \param diff_size Size of the diffusion kernel.
        */
        c_world(unsigned int width, unsigned int height, unsigned int diff_size = 3);
        /*!
            \brief Place an agent into the world.
            \param position Coordinates of the cell into which the agent should be placed.
            \return True if agent was placed succesfully.
            \return False if agent could not be placed (cell was already occupied).
        */
        bool place_agent(const s_ui_vec2 &position);
        /*!
            \brief Move agent from one position to another. 
            Input positions are floating point and are caster internally into the grid cell coordinates.
            \param from Coordinates from which the agent should be moved.
            \param to Coordinates to which the agent should be moved.
            \return True if agent was moved succesfully.
            \return False if any coordinates are out-of-bounds.
            \return False if there is no agent at <from> postion.
            \return False if there is already an agent at <to> cell.
        */
        bool move_agent(const s_f_vec2 &from, const s_f_vec2 &to);
        /*!
            \brief Move agent from one position to another. Input positions are grid cell coordinates.
            \param from Coordinates of the cell from which the agent should be moved.
            \param to Coordinates of the cell to which the agent should be moved.
            \return True if agent was moved succesfully.
            \return False if any coordinates are out-of-bounds.
            \return False if there is no agent at <from> postion.
            \return False if there is already an agent at <to> cell.
        */
        bool move_agent(const s_ui_vec2 &from, const s_ui_vec2 &to);
        /*!
            \brief Validate if agent can be moved from one position to another. 
            Input positions are floating point and are caster internally into the grid cell coordinates.
            \param from Coordinates from which the agent should be moved.
            \param to Coordinates to which the agent should be moved.
            \return True if agent can be moved succesfully.
            \return False if any coordinates are out-of-bounds.
            \return False if there is no agent at <from> postion.
            \return False if there is already an agent at <to> cell.
        */
        bool validate_move(const s_f_vec2 &from, const s_f_vec2 &to) const;
        /*!
            \brief Validate if agent can be moved from one position to another. Input positions are grid cell coordinates.
            \param from Coordinates of the cell from which the agent should be moved.
            \param to Coordinates of the cell to which the agent should be moved.
            \return True if agent can be moved succesfully.
            \return False if any coordinates are out-of-bounds.
            \return False if there is no agent at <from> postion.
            \return False if there is already an agent at <to> cell.
        */
        bool validate_move(const s_ui_vec2 &from, const s_ui_vec2 &to) const;
        /*!
            \brief Read trail map value at <position>.
            Input positions are floating point and are caster internally into the grid cell coordinates.
            \param position Coordinates from which the trail value should be read.
            \return Trail value at <position>.
            \return 0 if out-of-bounds.
        */
        unsigned short sense_world(const s_f_vec2 &position) const;
        /*!
            \brief Read trail map value at <position>.
            Input positions are grid cell coordinates.
            \param position Coordinates of the cell from which the trail value should be read.
            \return Trail value at <position>.
            \return 0 if out-of-bounds.
        */
        unsigned short sense_world(const s_ui_vec2 &position) const;
        /*!
            \brief Deposit <value> in the trail map.
            Input positions are floating point and are caster internally into the grid cell coordinates.
            \param position Coordinates to which the trail deposit should be deposited.
            \param position Coordinates to which the trail deposit should be deposited.
        */
        void deposit_trail(const s_f_vec2 &position, unsigned short value);
        /*!
            \brief Deposit <value> in the trail map.
            Input positions are grid cell coordinates.
            \param position Coordinates of the cell to which the trail deposit should be deposited.
            \param position Coordinates of the cell to which the trail deposit should be deposited.
        */
        void deposit_trail(const s_ui_vec2 &position, unsigned short value);
        /*!
            \brief Check if floating point coordinates are casted into the same grid cell.
            \param from Float coordinates 1.
            \param to Float coordinates 2.
            \return True if coordinates are for the same grid cell
            \return False if coordinates are for different grid cells
        */
        bool same_cell(const s_f_vec2 &from, s_f_vec2 &to) const;
        /*!
            \brief Diffuse the trail map. Apply 3x3 average filter to trail map.
        */
        void diffuse();
        /*!
            \brief Decay the trail map.
        */
        void decay();
        /*!
            \brief Display world map and trail map in the OpenCV window.
            \param delay Window delay (see OpenCV implementation).
        */
        void display(int delay) const;
    private:
        /*!
            \brief Cast float position into grid map coordinates
            \param position Float position.
            \return Grid map coordiantes
        */
        s_ui_vec2 to_grid(const s_f_vec2 &position) const;
        /*!
            \brief Check if <position> is in-bounds of the world.
            \param position Grid cell coordinates.
            \return True if <position> is within the world
            \return False if <position> out-of-bounds
        */
        bool check_inbounds(const s_ui_vec2 &position) const;
        /*!
            \brief Check if cell at <position> is empty.
            \note This function is not safe, you need to make sure prior to calling that <position> is in-bounds
            \param position Grid cell coordinates to check.
            \return True if cell at <position> is empty.
            \return False if cell at <position> is occupied.
        */
        bool check_cell_empty(const s_ui_vec2 &position) const;
        cv::Mat m_world_grid;
        cv::Mat m_trail_grid;
        cv::Mat m_diff_kernel;
        unsigned int m_width;
        unsigned int m_height;
};