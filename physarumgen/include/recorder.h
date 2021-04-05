#pragma once

#include <opencv2/core.hpp>
#include <string>

class c_recorder
{
    public:
        c_recorder(unsigned int width, unsigned int height, const std::string &path);
        void video_add_frame(const cv::Mat &frame) const;
        void save_image(const cv::Mat &frame) const;
    private:
        unsigned int m_frame_number = 0;
};