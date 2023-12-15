#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Cargar la imagen desde un archivo
    //cv::Mat imagen = cv::imread("radiografia.png", cv::IMREAD_GRAYSCALE);
    cv::Mat in(10, 10, CV_8U, cv::Scalar(7));
    //std::cout << in << std::endl;
    cv::Mat out(1, 11, CV_8U);
    for(int i = 0; i < in.rows; i+= 2){
        cv::Mat hor(2, 1, CV_8U);
            for(int j = 0; j < in.cols; j +=2){
                //tengo que hacer una matriz (2*r + 1, 2*r + 1)
                //cv::Mat aux, rhist, rlkt, resul;
                cv::Mat aux;
                in(cv::Rect(j,i,2,2)).copyTo(aux);
                //tengo que computarle el histograma
                //rhist = fsiv_compute_histogram(aux, rhist);
                //tengo que crear la lookup table y aplicarsela
                //rlkt = fsiv_create_equalization_lookup_table(rhist, hold_median);
                //fsiv_apply_lookup_table(aux, rlkt, resul);
            //voy concatenando horizontalmente
            cv::hconcat(hor, aux, hor);
            
            }
            std::cout << "Aux "<<hor<<std::endl;
        //concateno verticalmente  
        cv::hconcat(out, hor, out);
        std::cout << out <<std::endl;
        }  
    

    return 0;
}
