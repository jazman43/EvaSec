#include "Header/FileManagment.h"


void FileManagment::SetupFolder(int camID)
{    
    recorndingStartTime = std::chrono::steady_clock::now(); // Store start time
    time(&timeStamp);
    
    recFolder = "Recording";
    camFolder = recFolder + "/" + "Camera_" + std::to_string(camID);

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
    oss << "Cam_" << camID << "_Date_&_Time_" << std::put_time(std::localtime(&timeStamp), "%d-%m-%y_%H-%M-%S") << ".mp4";
    std::string filename = oss.str();
    
    std::string fullPath = camFolder + "/" + filename ; 

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

void FileManagment::CheckOldRecording()
{
    //                      days hours min seconds
    const int maxInSeconds = 3 * 24 * 60 * 60; // 3 days
    //const int maxInSeconds = 15 * 60 ; //15 mins test
    time_t now = time(nullptr);

    
    for(const auto& entry : std::filesystem::directory_iterator(camFolder))
    {
        if(entry.is_regular_file() && entry.path().extension() == ".mp4")
        {
            std::string fileName = entry.path().filename().string();

            size_t datePos = fileName.find("Date_&_Time_");
            size_t dotPos  = fileName.find(".mp4");

            
            if(datePos != std::string::npos && dotPos != std::string::npos)
            {
                std::string dateTimeStr = fileName.substr(datePos + 12, dotPos - (datePos + 12));

                std::tm fileTimeTm = {};
                std::istringstream ss(dateTimeStr);
                ss >> std::get_time(&fileTimeTm, "%d-%m-%y_%H-%M-%S");

                if(!ss.fail())
                {
                    fileTimeTm.tm_isdst = -1; // Let system handle DST
                    time_t fileTime = std::mktime(&fileTimeTm);

                    if (fileTime != -1)
                    {
                        
                        if (now - fileTime > maxInSeconds)
                        {
                            std::filesystem::remove(entry.path());
                            std::cout << "Deleted old recording: " << entry.path() << "\n";
                        }                  
                        
                    }
                }
                else
                {
                    std::cerr << "Error parsing timestamp from fileName: " << fileName << "\n";
                }

                
                
            }
        }
    }
}