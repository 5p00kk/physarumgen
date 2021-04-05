/* TODO fix all these paths etc */

#include "recorder.h"
#include <opencv2/imgcodecs.hpp>

c_recorder::c_recorder(unsigned int width, unsigned int height, const std::string &path)
    : m_path{path}
    , m_video_writer{(path+"physarum.mp4"), cv::VideoWriter::fourcc('A', 'V', 'C', '1'), 30, cv::Size(height, width), false}
{}

void c_recorder::video_add_frame(const cv::Mat &frame)
{
    m_video_writer.write(frame);
}

void c_recorder::save_image(const cv::Mat &frame)
{
    std::string image_path = m_path + "physarum_" + std::to_string(m_frame_number) + ".jpg";
    cv::imwrite(image_path, frame);
    m_frame_number++;
}