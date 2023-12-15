#include <iostream>
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

cv::Mat
fsiv_combine_images(const cv::Mat& foreground, const cv::Mat& background,
               const cv::Mat& mask)
{
    CV_Assert(background.size()==foreground.size());
    CV_Assert(background.type()==foreground.type());
    CV_Assert(mask.size() == foreground.size());
    cv::Mat output;
    //TODO
    // HINT: you can copy the backg on the foreg using the mask.

    output = foreground.clone();

    // Obtener las dimensiones de las imágenes de primer plano y fondo
    int rows = foreground.rows;
    int cols = foreground.cols;

    // Iterar sobre cada píxel de la máscara
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Obtener el valor del píxel en la máscara
            uchar maskPixel = mask.at<uchar>(i, j);

            // Si el valor del píxel en la máscara es mayor que 0, es un píxel del primer plano
            if (maskPixel > 0) {
                // Obtener el color del píxel en el primer plano
                cv::Vec3b foregroundPixel = foreground.at<cv::Vec3b>(i, j);

                // Combinar el píxel del primer plano con el fondo usando la máscara
                output.at<cv::Vec3b>(i, j) = foregroundPixel;
            }
            // Si el valor del píxel en la máscara es 0, es un píxel del fondo y no se hace nada
        }
    }

    // Combinar la imagen combinada con el fondo usando la inversa de la máscara
    cv::Mat invertedMask;
    bitwise_not(mask, invertedMask);
    background.copyTo(output, invertedMask);

    //
    CV_Assert(output.size() == foreground.size());
    CV_Assert(output.type()==foreground.type());
    return output;
}

cv::Mat
fsiv_create_mask_from_hsv_range(const cv::Mat& img,
                                 const cv::Scalar& lower_bound,
                                 const cv::Scalar& upper_bound)
{
    CV_Assert(img.channels() == 3);

    cv::Mat hsvImg;
    cv::cvtColor(img, hsvImg, cv::COLOR_BGR2HSV);

    cv::Mat mask;
    cv::inRange(hsvImg, lower_bound, upper_bound, mask);
    return mask;
}

cv::Mat
fsiv_apply_chroma_key(const cv::Mat &foreg, const cv::Mat& backg, int hue,
                           int sensitivity)
{
    cv::Mat out;
    cv::Scalar lower_b, upper_b; //HSV range.

    //TODO
    //Hint: use fsiv_xxx defined functions.
    //Hint: use all range for channels S and V.
    //Remember: the backg img must have the same dimensions to combine with
    //  foreg img. You can use cv::resize to assure this.

    lower_b = cv::Scalar(hue - sensitivity, 0, 0);
    upper_b = cv::Scalar(hue + sensitivity, 255,255); //ESTO ESTA CASI BINE PERO SERIA UPPER = HUE + SESITIVITY

    //USAMOS LAS DE CREAR MASCARA
    
    auto mask = fsiv_create_mask_from_hsv_range(foreg, lower_b, upper_b);
    
    //si el fondo .size es dintinto a back.size hay que resize el fore y back con el fore.size
    cv::Mat resizedBackg;
    backg.copyTo(resizedBackg);
    if(foreg.size() != backg.size())
        cv::resize(backg, resizedBackg, foreg.size());
    //usamos las de combinar, pero no combinar normal sino la MASCARA INVERTIDA :(
    
    out = fsiv_combine_images(foreg, resizedBackg, ~mask);
    //std::cout<<"Tamaño: "<<foreg.size()<<" tipo: "<<foreg.type()<<std::endl;
    //std::cout<<"Tamaño: "<<resizedBackg.size()<<" tipo: "<<resizedBackg.type()<<std::endl;
    //
    CV_Assert(out.size()==foreg.size());
    CV_Assert(out.type()==foreg.type());
    return out;
}