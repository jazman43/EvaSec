#include "Header/FileManagment.h"


void FileManagment::SetupFolder(int camID)
{    
    recorndingStartTime = std::chrono::steady_clock::now(); // Store start time
    time(&timeStamp);
    
    recFolder = "Recording";
    camFolder = recFolder + "/" +"Camera_" + std::to_string(camID);

    if(!std::filesystem::exists(recFolder))
    {
        if(!std::filesystem::create_directory(recFolder))
        {
            std::cerr << "Error: Failed to create directory: " << recFolder << "\n";
            return;
        }
        
    }

    if(!std::filesystem::exists(camFolder))
    {
        std::cout << "camera folder created: " << camFolder<< "\n";
        if(!std::filesystem::create_directory(camFolder))
        {
            std::cerr << "Error: Failed to create directory: " << camFolder << "\n";
            return;
        }
    }
    
    

    std::ostringstream oss;
    oss << "Cam_" << camID << "_Time_" << std::put_time(std::localtime(&timeStamp), "%d-%m-%y_%H-%M-%S") << ".mp4";
    std::string filename = oss.str();
    
    std::string fullPath = recFolder + "/" + filename ; 

    int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); 

    writer.open(fullPath, codec, fps, frameSize);

    if(!writer.isOpened())
    {
        std::cerr << "Error: Could not open video file for writing at " << fullPath << "\n";
    }else
    {
        std::cout << "Recording saved to: " << fullPath << "\n";
        
    }

    
}

void FileManagment::SaveVidoRecording(cv::Mat& frame)
{
    if(writer.isOpened())
    {
        writer.write(frame);
    }else {
        std::cerr << "Error: Video writer is not initialized.\n";
    }
}//

void FileManagment::CheckAndRotateRecording(int camID)
{

    auto now = std::chrono::steady_clock::now();
    int elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - recorndingStartTime).count();

    if (elapsedTime >= recordingDuration) 
    {
        std::cout << "Time limit reached. Rotating recording...\n";
        writer.release();  // Close current video file
        SetupFolder(camID); // Start a new recording
    }

}