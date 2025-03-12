#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


#include "Header/Camera.h"

int main()
{
    std::vector<std::shared_ptr<Camera>> cameras;

    

    for(int i = 0; i < 2; i++)
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
