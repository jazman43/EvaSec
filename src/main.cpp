#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <filesystem>

//liunx - 
#include <unistd.h>
#include <limits.h>


#include "Header/Camera.h"

#define CAMERAS_AMOUNT 1// amount of cameras we want to check for TODO make accessable to web portal

std::filesystem::path GetDirPath()
{
    char buffer[PATH_MAX];

    ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    if(count != -1)
    {
        return std::filesystem::path(std::string(buffer, count)).parent_path();
    }

    throw std::runtime_error("failed to get path");
}

int main()
{
    std::vector<std::shared_ptr<Camera>> cameras;
    
    try {
        std::filesystem::path dirPath = GetDirPath();
        std::filesystem::current_path(dirPath);
        std::cout << "Working directory set to: " << std::filesystem::current_path() << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error setting working directory: " << e.what() << "\n";
    }
    
    
    for(int i = 0; i < CAMERAS_AMOUNT; i++)
    {
        std::shared_ptr<Camera> cam = std::make_shared<Camera>(i);
        if(cam->Open())
        {
            cameras.push_back(std::move(cam));
        }else
        {
            std::cout << "Skipping camera " << i << " (not available)\n";
        }
    }

    
        
    while (true)
    {
        for(auto& cam : cameras)
        {
            cam->CameraUpdate();
        }
        

        if(cv::waitKey(30) == 'q')
        {
            break;
        }
        /* code */
    }
    
    
    

    cv::destroyAllWindows();
    return 0;
}
