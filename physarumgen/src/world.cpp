#include "world.h"
#include <opencv2/imgproc.hpp>

c_world::c_world(unsigned int width, unsigned int height, unsigned int diff_size)
    : m_width{width}
    , m_height{height}
    , m_world_grid{height, width, CV_8UC1, cv::Scalar(0)}
    , m_trail_grid{height, width, CV_8UC1, cv::Scalar(0)}
{
    /* Create diffusion kernel */
    m_diff_kernel = cv::Mat::ones(diff_size, diff_size, CV_32F)/(float)(diff_size*diff_size);

    /* Create windows */
    cv::namedWindow("world");
    cv::moveWindow("world", 500, 300);
    cv::namedWindow("trail");
    cv::moveWindow("trail", m_width + 500, 300);
}


bool c_world::place_agent(const s_ui_vec2 &position)
{
    bool ret_val = false;

    if(check_inbounds(position) && check_cell_empty(position))
    {
        m_world_grid.at<uchar>(position.y, position.x, 0) = 255;
        ret_val = true;
    }

    return ret_val;
}


bool c_world::validate_move(const s_f_vec2 &from, const s_f_vec2 &to) const
{
    return validate_move(to_grid(from), to_grid(to));
}


bool c_world::validate_move(const s_ui_vec2 &from, const s_ui_vec2 &to) const
{
    bool ret_val = false;

    /* Make sure that the orioginal cell is occupied */
    if(check_inbounds(from) && !check_cell_empty(from))
    {
        /* Check if destination cell is empty and in bounds */
        if(check_inbounds(to) && check_cell_empty(to))
        {
            ret_val = true;
        }
    }

    return ret_val;
}


bool c_world::move_agent(const s_f_vec2 &from, const s_f_vec2 &to)
{
    return move_agent(to_grid(from), to_grid(to));
}


bool c_world::move_agent(const s_ui_vec2 &from, const s_ui_vec2 &to)
{
    bool ret_val = false;

    if(validate_move(from, to))
    {
        ret_val = true;
        m_world_grid.at<uchar>(from.y, from.x, 0) = 0;
        m_world_grid.at<uchar>(to.y, to.x, 0) = 255;
    }

    return ret_val;
}


uchar c_world::sense_world(const s_f_vec2 &position) const
{
    return sense_world(to_grid(position));
}


uchar c_world::sense_world(const s_ui_vec2 &position) const
{
    uchar ret_val = 0;

    if(check_inbounds(position))
    {
        ret_val = m_trail_grid.at<uchar>(position.y, position.x, 0);
    }

    return ret_val;
}


void c_world::deposit_trail(const s_f_vec2 &position, uchar value)
{
    return deposit_trail(to_grid(position), value);
}


void c_world::deposit_trail(const s_ui_vec2 &position, uchar value)
{
    uchar trail_value = m_trail_grid.at<uchar>(position.y, position.x, 0);

    if(check_inbounds(position) && trail_value <= (255 - value))
    {
        m_trail_grid.at<uchar>(position.y, position.x, 0) += value;
    }
}


bool c_world::same_cell(const s_f_vec2 &from, s_f_vec2 &to) const
{
    return to_grid(from) == to_grid(to);
}


void c_world::diffuse()
{
    cv::filter2D(m_trail_grid, m_trail_grid, -1, m_diff_kernel, cv::Point(-1,-1));
}


void c_world::decay()
{

}


void c_world::display(int delay) const
{
    cv::imshow("world", m_world_grid);
    cv::imshow("trail", m_trail_grid);
    cv::waitKey(delay);
}


bool c_world::check_inbounds(const s_ui_vec2 &position) const
{
    return((position.x >= 0) && (position.x < m_width) && 
           (position.y >= 0) && (position.y < m_height)  );
}


bool c_world::check_cell_empty(const s_ui_vec2 &position) const
{
    return (m_world_grid.at<uchar>(position.y, position.x, 0) == 0);
}


s_ui_vec2 c_world::to_grid(const s_f_vec2 &position) const
{
    s_ui_vec2 ret_val;
    ret_val.x = std::round(position.x);
    ret_val.y = std::round(position.y);
    return ret_val;
};