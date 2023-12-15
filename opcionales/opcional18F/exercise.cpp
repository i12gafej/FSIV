#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
void
fsiv_compactTransform(const std::vector<cv::Mat> & list, cv::Mat & T){
    for(int i = 1; i < list.size(); i++)  {
        if(list[i-1].cols < list[i].rows){
            auto aux = cv::Mat::zeros(1, )
        }
        
        
        m++;
    }
}