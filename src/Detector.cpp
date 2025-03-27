#include "Header/Detector.h"


bool Detector::DetectPerson(cv::Mat& frame)
{
    
    static cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    std::vector<cv::Rect> people;
    hog.detectMultiScale(frame, people);

    if(!people.empty())
    {
        person++;
        std::cout << "person setected!!" << std::to_string(person) << "\n";

        for(const auto& rect : people)
        {
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        }
        
        return true;
    }
    return false;
}