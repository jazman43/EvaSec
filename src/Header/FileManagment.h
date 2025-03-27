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
    std::string camFolder;   

    int fps = 30;

    cv::Size frameSize = {640, 480};

    time_t timeStamp;

    std::chrono::steady_clock::time_point recorndingStartTime;
    const int recordingDuration = 10 * 60;

public:
    FileManagment(){}
    ~FileManagment(){}
    
    void SetupFolder(int camID);

    void SaveVidoRecording(cv::Mat& frame);

    void CheckAndRotateRecording(int camID);
    void CheckOldRecording();
    

private:

    cv::VideoWriter writer;

};

