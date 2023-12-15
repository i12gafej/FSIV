/**
 * @file histogram_features.hpp
 * (C) 2022- FJMC fjmadrid@uco.es
 */
#pragma once

#include "features.hpp"

class HistogramFeatures : public FeaturesExtractor
{
public:
    HistogramFeatures();
    ~HistogramFeatures();

    virtual std::string get_extractor_name() const override;
    virtual cv::Mat extract_features(const cv::Mat& img) override;

    // Add any additional methods or members if needed for the histogram feature extractor.
};
