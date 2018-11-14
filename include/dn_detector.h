//
// Created by lei on 18-11-14.
//

#ifndef DARKNET_DETECTOR_H
#define DARKNET_DETECTOR_H

#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

//#include <config.h>
//#include <frame.h>

#include "darknet.h"

namespace stereo_bm {
    class DNDetector{
    public:

        DNDetector(const std::string& cfgfile, const std::string& weightfile, const std::string& name_list);
        //    const string &mean_file, const string &mean_value);

        //std::vector<std::vector<float> > Detect(const cv::Mat &img);
        void Detect(const cv::Mat &img);
        //void Detect(std::shared_ptr<Frame> m_frame, std::shared_ptr<Config> m_config);

    private:
        void rgbgr_image_(image im);
        image ipl_to_image_(IplImage* src);
        image mat_to_image_(Mat m);
        char* string_to_cstr(const std::string str);

    private:
        //std::unique_ptr<tensorflow::Session> session;
        network *net;

        float thresh_ = 0.5;
        float hier_thresh_ = 0.5;
        float nms_=.45;
        char **names_;
    };
}

#endif //TF_EXAMPLE_DETECTOR_H
