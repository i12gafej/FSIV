#include "common_code.hpp"

cv::Mat
convert_image_byte_to_float(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.depth()==CV_8U);
    //TODO
    img.convertTo(out, CV_32F, 1.0 / 255.0);
    //
    CV_Assert(out.rows==img.rows && out.cols==img.cols);
    CV_Assert(out.depth()==CV_32F);
    CV_Assert(img.channels()==out.channels());
    return out;
}

cv::Mat
convert_image_float_to_byte(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.depth()==CV_32F);
    //TODO
    img.convertTo(out, CV_8U, 255.0);
    //
    CV_Assert(out.rows==img.rows && out.cols==img.cols);
    CV_Assert(out.depth()==CV_8U);
    CV_Assert(img.channels()==out.channels());
    return out;
}

cv::Mat
convert_bgr_to_hsv(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.channels()==3);
    //TODO
    cvtColor(img, out, cv::COLOR_BGR2HSV);
    //
    CV_Assert(out.channels()==3);
    return out;
}

cv::Mat
convert_hsv_to_bgr(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.channels()==3);
    //TODO
    cvtColor(img, out, cv::COLOR_HSV2BGR);
    //
    CV_Assert(out.channels()==3);
    return out;
}

cv::Mat
cbg_process (const cv::Mat & in, cv::Mat& out,
             double contrast, double brightness, double gamma,
             bool only_luma)
{
    CV_Assert(in.depth()==CV_8U);
    //TODO
    //Recuerda: es recomendable trabajar en flotante [0,1]
    //Después deshacer el cambio a byte [0,255]
    cv::Mat aux = in;
    if(aux.depth() == CV_8U)
        convert_image_byte_to_float(aux, aux);
    if(only_luma){
        //imagen a HVS
        convert_bgr_to_hsv(aux, aux);

        //creo los canales
        std::vector<cv::Mat> canalesHVS;
        cv::split(aux, canalesHVS);

        //calculo en la capa V
        cv::Mat power;
        cv::pow(canalesHVS[2], gamma, power);
        
        cv::Mat mult;
        cv::multiply(power, cv::Scalar::all(contrast), mult);

        cv::Mat sum;
        cv::add(mult, cv::Scalar::all(brightness), canalesHVS[2]);
        

        //uno los canales
        cv::merge(canalesHVS, aux);
        convert_hsv_to_bgr(aux, out);
    }
    else{
        cv::Mat power;
        cv::pow(aux, gamma, power);
        
        cv::Mat mult;
        cv::multiply(power, cv::Scalar::all(contrast), mult);

        cv::Mat sum;
        cv::add(mult, cv::Scalar::all(brightness), out);
    }
    
    convert_image_float_to_byte(out, out);

    //
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    CV_Assert(out.depth()==CV_8U);
    CV_Assert(out.channels()==in.channels());
    return out;
}
