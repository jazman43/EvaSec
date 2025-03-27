#pragma once
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>


class Detector
{
private:
    int person = 0;
public:
    Detector(/* args */){}
    ~Detector(){}

    bool DetectPerson(cv::Mat& frame);
};

