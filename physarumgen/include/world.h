#pragma once

#include "utils.h"
#include <opencv2/highgui.hpp>

class c_world
{
    public:
        c_world(unsigned int width, unsigned int height);
        bool place_agent(const s_ui_vec2 &position);
        bool move_agent(const s_f_vec2 &from, const s_f_vec2 &to);
        bool move_agent(const s_ui_vec2 &from, const s_ui_vec2 &to);
        bool validate_move(const s_f_vec2 &from, const s_f_vec2 &to) const;
        bool validate_move(const s_ui_vec2 &from, const s_ui_vec2 &to) const;
        uchar sense_world(const s_f_vec2 &position) const;
        uchar sense_world(const s_ui_vec2 &position) const;
        void deposit_trail(const s_f_vec2 &position, uchar value);
        void deposit_trail(const s_ui_vec2 &position, uchar value);
        bool grid_change(const s_f_vec2 &from, s_f_vec2 &to) const;
        void display(int delay) const;
    private:
        s_ui_vec2 to_grid(const s_f_vec2 &position) const;
        bool check_inbounds(const s_ui_vec2 &position) const;
        bool c_world::check_cell_empty(const s_ui_vec2 &position) const;
        cv::Mat m_world_grid;
        cv::Mat m_trail_grid;
        unsigned int m_width;
        unsigned int m_height;
};