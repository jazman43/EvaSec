#include "Header/FileManagment.h"


void FileManagment::SetupFolder(int camID)
{
    time(&timeStamp);

    

    if(!std::filesystem::exists(recFolder))
    {
        std::filesystem::create_directory(recFolder);
    }
    std::string filename = "Cam: " + std::to_string(camID) + " Time/Date: " + ctime(&timeStamp) + ".mp4";
    
    std::string fullPath = recFolder + "/" + filename ; 

    int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); 
    writer.open(fullPath, codec, fps, frameSize, true);

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open video file for writing at " << fullPath << "\n";
    } else {
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