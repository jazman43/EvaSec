#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
//CREATE CAMERA
#include "FileManagment.h"
#include "Detector.h"

class Camera
{
public:
    Camera(int camID);
    ~Camera(){ CameraCleanUp(); }

    
    bool Open(){ return cam.isOpened(); }

    //must be put into loop
    void CameraUpdate();

    void CameraCleanUp();

    //getters
    cv::VideoCapture GetCamera(){ return cam; }
    cv::Mat GetFrame(){ return frame; }

private:
    int id;

    cv::VideoCapture cam;
    
    cv::Mat frame;

    FileManagment fileManager;
    Detector detector;
};