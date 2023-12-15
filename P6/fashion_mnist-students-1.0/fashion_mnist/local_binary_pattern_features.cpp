/**
 * @file local_binary_pattern_features.cpp
 * (C) 2022- FJMC fjmadrid@uco.es
 */
#include <opencv2/imgproc.hpp>
#include "local_binary_pattern_features.hpp"
#include <iostream>

using namespace std;

LocalBinaryPatternFeatures::LocalBinaryPatternFeatures()
{
    type_ = FSIV_LOCAL_BINARY_PATTERN;
    params_ = {0.0};
    // You can initialize specific parameters for the extractor here if needed.
}

LocalBinaryPatternFeatures::~LocalBinaryPatternFeatures()
{
    // You can perform cleanup or resource release tasks here if needed.
}

std::string LocalBinaryPatternFeatures::get_extractor_name() const
{
    return "Local Binary Pattern";
}
cv::Mat reconstructImage(const cv::Mat& inputRow, int rows, int cols)
{
    if (inputRow.rows * inputRow.cols != rows * cols)
    {
        throw std::runtime_error("Invalid dimensions for image reconstruction.");
    }

    cv::Mat outputImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int index = i * cols + j;
            outputImage.at<uchar>(i, j) = inputRow.at<uchar>(0, index);
        }
    }

    return outputImage;
}
cv::Mat LocalBinaryPatternFeatures::extract_features(const cv::Mat& img)
{
    // Check if the image is in grayscale
    if (img.channels() != 1)
    {
        throw std::runtime_error("Input image must be in grayscale for Local Binary Pattern.");
    }
    cv::Mat img2 = img.clone();
    img2 = reconstructImage(img2, 28, 28);
    cv::Mat lbp;
    cv::Mat lbp_image = cv::Mat::zeros(img2.rows - 2, img2.cols - 2, CV_8UC1);

    for (int i = 1; i < img2.rows - 1; ++i)
    {
        for (int j = 1; j < img2.cols - 1; ++j)
        {
            uchar center = img2.at<uchar>(i, j);
            uchar code = 0;

            code |= (img2.at<uchar>(i - 1, j - 1) > center) << 7;
            code |= (img2.at<uchar>(i - 1, j) > center) << 6;
            code |= (img2.at<uchar>(i - 1, j + 1) > center) << 5;
            code |= (img2.at<uchar>(i, j + 1) > center) << 4;
            code |= (img2.at<uchar>(i + 1, j + 1) > center) << 3;
            code |= (img2.at<uchar>(i + 1, j) > center) << 2;
            code |= (img2.at<uchar>(i + 1, j - 1) > center) << 1;
            code |= (img2.at<uchar>(i, j - 1) > center) << 0;

            lbp_image.at<uchar>(i - 1, j - 1) = code;
        }
    }

    // Flatten the LBP matrix to a 1D row vector
    cv::Mat feature = lbp_image.reshape(1, 1);
    feature.convertTo(feature, CV_32FC1);

    CV_Assert(feature.rows == 1);
    CV_Assert(feature.type() == CV_32FC1);

    return feature;
}
