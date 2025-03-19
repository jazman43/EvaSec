#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <ctime>
#include <thread>


class FileManagment
{
private:
    std::string recFolder = "Recording";    

    int fps = 30;

    cv::Size frameSize = {640, 480};

    time_t timeStamp;
public:
    FileManagment(){}
    ~FileManagment(){}
    
    void SetupFolder(int camID);

    void SaveVidoRecording(cv::Mat& frame);

private:

    cv::VideoWriter writer;

};

