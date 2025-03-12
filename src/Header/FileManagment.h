#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <ctime>


class FileManagment
{
private:
    std::string recFolder = "Recording";

    cv::VideoWriter writer;

    int fps = 30;

    cv::Size frameSize = {640, 480};

    time_t timeStamp;
public:
    FileManagment(){}
    ~FileManagment(){}
    
    void SetupFolder(int camID);

    void SaveVidoRecording(cv::Mat& frame);
};

