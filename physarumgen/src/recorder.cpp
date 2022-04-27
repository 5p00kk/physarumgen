/* TODO fix all these paths etc */
/* TODO deal with exceptions / failures */

#include "recorder.h"
#include <opencv2/imgcodecs.hpp>

c_recorder::c_recorder()
{}

c_recorder::c_recorder(unsigned int width, unsigned int height, const std::string &path)
    : m_path{path}
{
    new_recording(width, height, path);
}

bool c_recorder::new_recording(unsigned int width, unsigned int height, const std::string &path)
{
    m_path = path;
    m_frame_number = 0;
    m_recording = m_video_writer.open((path+"physarum.mp4"), cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 30, cv::Size(height, width), false);
    return m_recording;
}

void c_recorder::stop_recording()
{
    m_video_writer.release();
    m_recording = false;
}

void c_recorder::video_add_frame(const cv::Mat &frame)
{
    if(m_recording)
    {
        m_video_writer.write(frame);
    }
}

void c_recorder::save_image(const cv::Mat &frame)
{
    if(m_recording)
    {
        std::string image_path = m_path + "physarum_" + std::to_string(m_frame_number) + ".png";
        cv::imwrite(image_path, frame);
        m_frame_number++;
    }
}