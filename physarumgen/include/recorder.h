#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <string>

class c_recorder
{
    public:
        c_recorder(unsigned int width, unsigned int height, const std::string &path);
        void video_add_frame(const cv::Mat &frame);
        void save_image(const cv::Mat &frame);
    private:
        std::string m_path;
        unsigned int m_frame_number = 0;
        cv::VideoWriter m_video_writer;
};