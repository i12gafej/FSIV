#include <iostream>
#include "common_code.hpp"

void 
fsiv_find_min_max_loc_1(cv::Mat const& input,
    std::vector<cv::uint8_t>& min_v, std::vector<cv::uint8_t>& max_v,
    std::vector<cv::Point>& min_loc, std::vector<cv::Point>& max_loc)
{
    CV_Assert(input.depth()==CV_8U);

    //! TODO: do a rows/cols scanning to find the first min/max values. 
    // Hint: use cv::split to get the input image channels.
    
    
    std::vector<cv::Mat> canales;
    cv::split(input, canales);
    for(size_t z = 0; z < canales.size(); z++){
        max_v.push_back(0);
        max_loc.push_back(cv::Point(0,0));
        min_v.push_back(255);
        min_loc.push_back(cv::Point(0,0));
        
        for(int i = 0; i < input.rows; i++){

            for(int j = 0; j < input.cols; j++){

                const auto v = canales[z].at<uchar>(i, j);
                
                if(v < min_v.at(z)){
                    min_v[z] = v;
                    min_loc[z] = cv::Point(i, j);
                    
                }
                if(v > max_v[z]){
                    max_v[z] = v;
                    max_loc[z] = cv::Point(i, j);
                    
                }   
                
            }
        }

    }
    //

    CV_Assert(input.channels()==min_v.size());
    CV_Assert(input.channels()==max_v.size());
    CV_Assert(input.channels()==min_loc.size());
    CV_Assert(input.channels()==max_loc.size());
}

void 
fsiv_find_min_max_loc_2(cv::Mat const& input,
    std::vector<double>& min_v, std::vector<double>& max_v,
    std::vector<cv::Point>& min_loc, std::vector<cv::Point>& max_loc)
{

    //! TODO: Find the first min/max values using cv::minMaxLoc function.    
    // Hint: use cv::split to get the input image channels.
    std::vector<cv::Mat> canales;
    cv::split(input, canales);

    for(int i = 0; i < canales.size(); i++){
        std::cout<<"Capa: "<<std::endl;
        double minVal = 0, maxVal= 0;
        cv::Point minLoc = cv::Point(0,0), maxLoc = cv::Point(0,0);
        cv::minMaxLoc(canales[i], &minVal,  &maxVal, &minLoc, &maxLoc);
        std::cout<<"MIN val:"<<minVal<<"   loc:"<<minLoc<<std::endl;
        std::cout<<"MAX val:"<<maxVal<<"   loc:"<<maxLoc<<std::endl;
        max_v.push_back(maxVal);
        max_loc.push_back(maxLoc);
        min_v.push_back(minVal);
        min_loc.push_back(minLoc);
    }


    //

    CV_Assert(input.channels()==min_v.size());
    CV_Assert(input.channels()==max_v.size());
    CV_Assert(input.channels()==min_loc.size());
    CV_Assert(input.channels()==max_loc.size());

}

