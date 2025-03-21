#include "Header/Camera.h"

Camera::Camera(int camID) : id(camID)
{
    cam.open(id);
    

    if(!cam.isOpened())
    {
        std::cerr << "failed to open camera " << id << "\n";        
    }else
    {
        fileManager.SetupFolder(id);
        std::cout << "Camera " << id << " has opened\n";
    }
}



void Camera::CameraUpdate()
{
    if(!cam.isOpened()){return;}
    cam >> frame;


    if(frame.empty())
    {
        std::cerr << "failed to grab frame " << id<< "\n";
    }    
    
    fileManager.SaveVidoRecording(frame);
    

    cv::imshow("EvaSecurity camera "+ std::to_string(id), frame);
    
    cv::waitKey(30);
}

void Camera::CameraCleanUp()
{
    if (cam.isOpened()) {
        cam.release();
        std::cout << "Camera " << id << " released.\n";
    }
}