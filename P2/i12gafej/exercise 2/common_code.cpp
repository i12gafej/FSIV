#include "common_code.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

cv::Mat fsiv_color_rescaling(const cv::Mat& in, const cv::Scalar& from, const cv::Scalar& to)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out;
    //TODO
    //Cuidado con dividir por cero.
    //Evita los bucles.
    cv::Scalar r;
    //out = ColorDestino/ColorOrigen * in
    cv::divide(to, from, r);
    out=in.mul(r);
    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_wp_color_balance(cv::Mat const& in)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out;
    //TODO
    //Sugerencia: utiliza el espacio de color GRAY para
    //saber la ilumimancia de un pixel.

    //convertimos a escala de grises
    cv::cvtColor(in, out, cv::COLOR_BGR2GRAY);

    //encontramos el punto de Maximo color
    cv::Point maxPoint, minPoint;
    double minN, maxN;
    cv::minMaxLoc(out , &minN, &maxN, &minPoint, &maxPoint);

    //rescalamos al blanco obtenido con respecto al blanco natural
    cv::Scalar blanco = in.at<cv::Vec3b>(maxPoint);
    out = fsiv_color_rescaling(in, blanco, cv::Scalar(255,255,255));

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_gw_color_balance(cv::Mat const& in)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out;
    //TODO

    //calculamos la media para reescalar a ese color griss
    cv::Scalar gris = cv::mean(in);
    out = fsiv_color_rescaling(in, gris, cv::Scalar(128,128,128));

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_color_balance(cv::Mat const& in, float p)
{
    CV_Assert(in.type()==CV_8UC3);
    CV_Assert(0.0f<p && p<100.0f);
    cv::Mat out;
    //TODO
    //Sugerencia: utiliza el espacio de color GRAY para
    //saber la ilumimancia de un pixel.
    cv::cvtColor(in, out, cv::COLOR_BGR2GRAY);
    
    int canales[] = {0};
    int numBins[] = {256}; 
    float rango[] = {0, 256};
    const float* histRanges[] = {rango};

    //calculamos el histograma de la imagen a gris y la normalizamos
    cv::Mat histograma;
    cv::calcHist(&out, 1, canales, cv::Mat(), histograma, 1, numBins, histRanges, true, false);
    cv::normalize(histograma, histograma, 1, 0, cv::NORM_L1, -1, cv::Mat());
    //calculamos el valor acumulado del histograma hasta que llegue al porcentaje
    float porcentaje = 1.0 - (p/100.0), accum = 0.0;
    int i = 0;
    
    while(i < histograma.rows && porcentaje >= accum){//recorremos el histograma hasta que el acumulador sea menor a porcentaje
        accum+=histograma.at<float>(i, 0);
        i++;
    }
    //calculamos la media y reescalamos con la media
    cv::Scalar media = cv::mean(in, out >= i);
    out = fsiv_color_rescaling(in, media, cv::Scalar(255, 255, 255));

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}
