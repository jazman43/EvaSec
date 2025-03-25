#include "Header/FileManagment.h"


void FileManagment::SetupFolder(int camID)
{    

    time(&timeStamp);
    
    recFolder = "Recording";

    if(!std::filesystem::exists(recFolder))
    {
        if(!std::filesystem::create_directory(recFolder))
        {
            std::cerr << "Error: Failed to create directory: " << recFolder << "\n";
            return;
        }
        
    }
    

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));


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