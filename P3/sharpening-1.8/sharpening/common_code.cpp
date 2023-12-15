#include <iostream>
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

cv::Mat
fsiv_create_gaussian_filter(const int r)
{
    CV_Assert(r>0);
    cv::Mat ret_v;

    // TODO 
    // Remember: 6*sigma is approx 99,73% of the distribution.
    float sigma = ((float)(2*r+1))/6.0;
    ret_v = cv::Mat::zeros(2*r+1, 2*r+1, CV_32F);

    for (int i = r; i >= -r; --i){
        for(int j = -r; j <= r; ++j){
            float dividendo = - (std::pow(i, 2) + std::pow(j, 2));
            float divisor = 2 * std::pow(sigma, 2);
            ret_v.at<float>(i+r, j+r) = std::exp(dividendo/divisor);
        }
    }

    cv::normalize(ret_v, ret_v, 1.0, 0.0, cv::NORM_L1);


    //
    CV_Assert(ret_v.type()==CV_32FC1);
    CV_Assert(ret_v.rows==(2*r+1) && ret_v.rows==ret_v.cols);
    CV_Assert(std::abs(1.0-cv::sum(ret_v)[0])<1.0e-6);
    return ret_v;
}

cv::Mat
fsiv_extend_image(const cv::Mat& img, const cv::Size& new_size, int ext_type)
{
    CV_Assert(img.rows<new_size.height);
    CV_Assert(img.cols<new_size.width);
    cv::Mat out;
    //TODO
    //Hint: use cv::copyMakeBorder()
    int pad = (new_size.height-img.rows)/2;
    if(ext_type == 0){
        cv::copyMakeBorder(img,out,pad,pad,pad,pad,cv::BORDER_CONSTANT);
    }else{
        cv::copyMakeBorder(img,out,pad,pad,pad,pad,cv::BORDER_WRAP);
    }
    //
    CV_Assert(out.type()==img.type());
    CV_Assert(out.rows == new_size.height);
    CV_Assert(out.cols == new_size.width);
    return out;
}

cv::Mat
fsiv_create_sharpening_filter(const int filter_type, int r1, int r2)
{
    CV_Assert(0<=filter_type && filter_type<=2);
    CV_Assert(0<r1 && r1<r2);
    cv::Mat filter;
    //TODO
    // Remember DoG = G[r2]-G[r1].
    // Hint: use fsiv_extend_image() to extent G[r1].
    // Remember: Use -Laplacian + [1] as filter.

    if (filter_type == 0){
        float imp[9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        float data_lap_4[9] = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };

        cv::Mat imp_mat = cv::Mat(3, 3, CV_32FC1, imp);
        cv::Mat lap_4 = cv::Mat(3, 3, CV_32FC1, data_lap_4);

        filter = imp_mat - lap_4;

    } else if (filter_type == 1) {
        float imp[9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        float data_lap_8[9] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };

        cv::Mat imp_mat = cv::Mat(3, 3, CV_32FC1, imp);        
        cv::Mat lap_8 = cv::Mat(3, 3, CV_32FC1, data_lap_8);

        filter = imp_mat - lap_8;

    } else if (filter_type == 2){
        cv::Mat G_r1 = fsiv_create_gaussian_filter(r1);
        cv::Mat G_r2 = fsiv_create_gaussian_filter(r2);

        G_r1 = fsiv_extend_image(G_r1, G_r2.size());

        cv::Mat imp_mat = cv::Mat::zeros(G_r1.size(), CV_32FC1);
        imp_mat.at<float>(r2, r2) = 1;

        cv::Mat dog = G_r2 - G_r1;
        filter = imp_mat - dog;
    }
    //
    CV_Assert(filter.type()==CV_32FC1);
    CV_Assert((filter_type == 2) || (filter.rows==3 && filter.cols==3) );
    CV_Assert((filter_type != 2) || (filter.rows==(2*r2+1) &&
                                     filter.cols==(2*r2+1)));
    return filter;
}



cv::Mat
fsiv_image_sharpening(const cv::Mat& in, int filter_type, bool only_luma,
                      int r1, int r2, bool circular)
{
    CV_Assert(in.depth()==CV_8U);
    CV_Assert(0<r1 && r1<r2);
    CV_Assert(0<=filter_type && filter_type<=2);
    cv::Mat out;
    
    // TODO
    // Hint: use cv::filter2D using cv::BORDER_ISOLATED.
    // Remember: if circular, first the input image must be circular extended,
    //  and then clip the result.
    cv::Mat filtro = fsiv_create_sharpening_filter(filter_type, r1, r2);
    cv::Size new_size (in.cols+(2*r2), in.rows+(2*r2));

    
    
    if(only_luma && in.channels() == 3){
        cv::Mat aux = in.clone();
        std::vector<cv::Mat> canales;
        cv::cvtColor(aux, aux, cv::COLOR_BGR2HSV);
        cv::split(aux, canales);

        if(circular){
            cv::Mat circulo = fsiv_extend_image(canales[2], new_size, 1);

            cv::filter2D(circulo, circulo, -1, filtro);

            circulo = circulo(cv::Rect(r2, r2, in.cols, in.rows));
            circulo.copyTo(canales[2]);
        }
        else{
            cv::Mat expansion = fsiv_extend_image(canales[2], new_size, 0);

            cv::filter2D(expansion, expansion, -1, filtro);

            expansion = expansion(cv::Rect(r2, r2, in.cols, in.rows));
            expansion.copyTo(canales[2]);
        }
        cv::merge(canales, aux);
        cv::cvtColor(aux, out, cv::COLOR_HSV2BGR);
    }

    else{
        cv::Mat img, expansion;

        if(circular){
            expansion = fsiv_extend_image(in,new_size,1);
        }
        else{
            expansion = fsiv_extend_image(in,new_size,0);
        }
        cv::filter2D(expansion, out, -1, filtro);
        out = out(cv::Rect(r2,r2,in.cols,in.rows));
    }

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.size()==in.size());
    return out;
}
