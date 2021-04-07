#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <string>

class c_recorder
{
    public:
        /*!
            \brief Constructor. No recording started
        */
        c_recorder();
        /*!
            \brief Constructor. Starts recording automatically
            \param width Width of the recording
            \param height Height of the recording
            \param path Folder where recording should be saved
            \note For now path has to end with '/', no checks if path exsits.
        */
        c_recorder(unsigned int width, unsigned int height, const std::string &path);
        /*!
            \brief Start new recording.
            \param width Width of the recording
            \param height Height of the recording
            \param path Folder where recording should be saved
            \note For now path has to end with '/', no checks if path exsits.
        */
        bool new_recording(unsigned int width, unsigned int height, const std::string &path);
        /*!
            \brief Stop current recording.
        */
        void stop_recording();
        /*!
            \brief Add frame to the video recording.
            \param frame Video frame
            \note <frame> size has to match the vidoe size selected when starting a recording.
        */
        void video_add_frame(const cv::Mat &frame);
        /*!
            \brief Save image snapshot into the recording folder.
            \param frame Image frame
        */
        void save_image(const cv::Mat &frame);
        /*!
            \brief Is recording active.
        */
        bool m_recording = false;
    private:
        cv::VideoWriter m_video_writer;
        std::string m_path;
        unsigned int m_frame_number = 0;
};