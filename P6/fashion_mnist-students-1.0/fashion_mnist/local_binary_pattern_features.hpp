/**
 * @file local_binary_pattern_features.hpp
 * (C) 2022- FJMC fjmadrid@uco.es
 */
#pragma once

#include "features.hpp"

class LocalBinaryPatternFeatures : public FeaturesExtractor
{
public:
    LocalBinaryPatternFeatures();
    ~LocalBinaryPatternFeatures();

    virtual std::string get_extractor_name() const override;
    virtual cv::Mat extract_features(const cv::Mat& img) override;

    // No need to override these methods for this extractor
    // virtual void train(const cv::Mat& samples) override;
    // virtual bool save_model(std::string const& fname) const override;
    // virtual bool load_model(std::string const& fname) override;
};
cv::Mat reconstructImage(const cv::Mat& inputRow, int rows, int cols);
