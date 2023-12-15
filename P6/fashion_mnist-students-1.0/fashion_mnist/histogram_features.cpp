/**
 * @file histogram__features.cpp
 * (C) 2022- FJMC fjmadrid@uco.es
 */
#include <opencv2/imgproc.hpp>
#include "histogram_features.hpp"

using namespace std;

// Implement the methods for the HistogramFeatures class.
// You'll need to define the virtual functions declared in the header file.

HistogramFeatures::HistogramFeatures()
{
    type_ = FSIV_HISTOGRAM;
    params_ = {0.0};
    // Puedes inicializar parámetros específicos del extractor aquí si es necesario.
}

HistogramFeatures::~HistogramFeatures()
{
    // Puedes realizar tareas de limpieza o liberación de recursos aquí si es necesario.
}
std::string
HistogramFeatures::get_extractor_name() const
{
    std::string name;
    switch(int(params_[0])){
        case 0:
            name = "Simple Histogram.";
            break;
        case 1:
            name = "Gradient Histogram.";
            break;
        default:
            throw std::runtime_error("unknown type of histogram extractor.");
            break;
    }
    return name;
}
cv::Mat
fsiv_simple_histogram(cv::Mat const& img)
{
    // TODO: Extract  histogram features from the input image.
    // Hint: You can use cv::cvtColor to convert the image to .
    // Hint: Use cv::calcHist to compute the histogram.
    // Hint: Flatten the histogram matrix to a 1D row vector.
    cv::Mat feature;
    if (img.channels() != 1)
    {
        throw std::runtime_error("Input image must be in grayscale.");
    }

    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    cv::Mat hist;

    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false);
    feature = hist.reshape(1, 1);
    feature.convertTo(feature, CV_32FC1);

    CV_Assert(feature.rows==1);
    CV_Assert(feature.type()==CV_32FC1);
    return feature;
}

cv::Mat
fsiv_gradient_histogram(cv::Mat const& img)
{
    cv::Mat feature;
    if (img.channels() != 1)
    {
        throw std::runtime_error("Input image must be in grayscale.");
    }

    // Calculate the gradient using the Sobel operator
    cv::Mat grad_x, grad_y;
    cv::Sobel(img, grad_x, CV_32F, 1, 0, 3);
    cv::Sobel(img, grad_y, CV_32F, 0, 1, 3);

    // Calculate the magnitude of the gradient
    cv::Mat magnitude;
    cv::magnitude(grad_x, grad_y, magnitude);

    // Calculate the histogram of the gradient magnitude
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    cv::Mat hist;

    cv::calcHist(&magnitude, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false);
    
    // Flatten the histogram matrix to a 1D row vector
    feature = hist.reshape(1, 1);
    feature.convertTo(feature, CV_32FC1);

    CV_Assert(feature.rows == 1);
    CV_Assert(feature.type() == CV_32FC1);

    return feature;
}
cv::Mat
HistogramFeatures::extract_features(const cv::Mat& img)
{
    cv::Mat feature;    
    switch (int(params_[0]))
    {
        case 0:
            feature = fsiv_simple_histogram(img);
            break;
        case 1:
            feature = fsiv_gradient_histogram(img);
            break;
        default:
            throw std::runtime_error("unknown type of histogram extractor.");
            break;
    }
    CV_Assert(feature.rows == 1);
    CV_Assert(feature.type() == CV_32FC1);

    return feature;
}
