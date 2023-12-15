#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "common_code.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
void 
fsiv_compute_derivate(cv::Mat const& img, cv::Mat& dx, cv::Mat& dy, int g_r, 
    int s_ap)
{
    CV_Assert(img.type()==CV_8UC1);
    // TODO
    // Hint: if g_r > 0 apply a Gaussian Blur operation with kernel size 2*g_r+1.
    // Hint: use Sobel operator to compute derivate.

    if (g_r > 0) {
        cv::GaussianBlur(img, img, cv::Size(2 * g_r + 1, 2 * g_r + 1), 0, 0);
    }

    cv::Sobel(img, dx, CV_32F, 1, 0, s_ap);
    cv::Sobel(img, dy, CV_32F, 0, 1, s_ap);

    //if(g_r > 0){
      //blur  
    //}
    // Mat sobelx, sobely;
    // for(int i = 0; i < s_ap; i++){
    //     cv::Mat filax, filay;
    //     for(int j = 0; j < s_ap; j++){
            
    //         //casuistica de x
    //             //si j != medio
    //                 //valor celda i j = (s_ap) / 2 - i --> (5/2 - 0 = 2) (5/2 - 1 = 1) (5/2 - 2 = 0)
    //             //else
    //                 //valor celda i j = ((s_ap) / 2 - i)* 2 
    //         //para y es lo mismo pero invirtiendo i e j
    //         if(j != s_ap/2+1){
    //             cv::Mat elemento = (cv::Mat_<int>(1,1) << ((s_ap) / 2 - i));
    //             if(filax.empty()){
    //                 filax = elemento.clone();
    //             }
    //             else{
    //                 cv::hconcat(filax, elemento, filax);
    //             }
    //             if(filay.empty()){
    //                 filay = elemento.clone();
    //             }
    //             else{
    //                 cv::vconcat(filay, elemento, filay);
    //             }
    //         }
    //         else{
    //             cv::Mat elemento = (cv::Mat_<int>(1,1) << (((s_ap) / 2 - i)* 2 ));
    //             cv::hconcat(filax, elemento, filax);
    //             cv::vconcat(filay, elemento, filay);
    //         }
    //     }
    //     if(sobelx.empty() && sobely.empty()){
    //         sobelx = filax.clone();
    //         sobely = filay.clone();
    //     }
    //     else{
    //         cv::hconcat(sobelx, filax, sobelx);
    //         cv::vconcat(sobely, filay, sobely);
    //     }
    // }

    //
    CV_Assert(dx.size()==img.size());
    CV_Assert(dy.size()==dx.size());
    CV_Assert(dx.type()==CV_32FC1);
    CV_Assert(dy.type()==CV_32FC1);
}

void 
fsiv_compute_gradient_magnitude(cv::Mat const& dx, cv::Mat const& dy,
    cv::Mat& gradient)
{
    CV_Assert(dx.size()==dy.size());
    CV_Assert(dx.type()==CV_32FC1);
    CV_Assert(dy.type()==CV_32FC1);

    // TODO
    // Hint: use cv::magnitude.
    cv::magnitude(dx, dy, gradient);
    //

    CV_Assert(gradient.size()==dx.size());
    CV_Assert(gradient.type()==CV_32FC1);
}

void
fsiv_compute_gradient_histogram(cv::Mat const& gradient, int n_bins, 
cv::Mat& hist, float & max_gradient)
{   
    // TODO
    // Hint: use cv::minMaxLoc to get the gradient range {0, max_gradient}
    // Remember: use cv::normalize to get a normalized histogram.
    double min_val, max_val;
    cv::minMaxLoc(gradient, &min_val, &max_val);
    max_gradient = static_cast<float>(max_val);
    

    float rango[] = {0, max_gradient};
    const float* histRanges[] = {rango};
    cv::calcHist(&gradient, 1, 0, cv::Mat(), hist, 1, &n_bins, histRanges, true, false);
    cv::normalize(hist, hist, 1.0, 0.0, cv::NORM_L1);
    //
    CV_Assert(max_gradient>0.0);
    CV_Assert(hist.rows == n_bins);
    CV_Assert(cv::abs(cv::sum(hist)[0]-1.0)<1.e-6);
}

int
fsiv_compute_histogram_percentile(cv::Mat const& hist, float percentile)
{
    CV_Assert(percentile>=0.0 && percentile<=1.0);
    CV_Assert(hist.type()==CV_32FC1);
    CV_Assert(hist.cols==1);
    CV_Assert(cv::abs(cv::sum(hist)[0]-1.0)<1.e-6);
    int idx = 0;
    // TODO
    // Remember: The percentile p is the first i that sum{h[0], h[1], ..., h[i]} >= p    
    
    float acumulado = 0.0;


    for (; idx < hist.rows; ++idx) {
        acumulado += hist.at<float>(idx);
        if (acumulado >= percentile || std::abs(acumulado - percentile) < 1.e-6) {
            // std::cout <<"acumulado:" <<acumulado << std::endl;
            // std::cout <<"percentile:" <<percentile << std::endl;
            // std::cout <<"idx:" <<idx << std::endl;
            break;
        }
    }
    
    
    // std::cout << std::endl;
    // std::cout << "idx: " << idx << "==(hist.rows-1: "<< hist.rows-1 <<")"<<std::endl;
    // std::cout << "cv::sum(hist(cv::Range(0, idx+1), cv::Range::all()))[0]: " << cv::sum(hist(cv::Range(0, idx+1), cv::Range::all()))[0] << ">=percentile: "<<std::endl;
    //
    CV_Assert(idx>=0 && idx<hist.rows);
    CV_Assert(idx<=0 || cv::sum(hist(cv::Range(0, idx), cv::Range::all()))[0]<=percentile);
    CV_Assert(idx==(hist.rows-1) || cv::sum(hist(cv::Range(0, idx+1), cv::Range::all()))[0]>=percentile);
    return idx;
}

float 
fsiv_histogram_idx_to_value(int idx, int n_bins, float max_value,
    float min_value)
{
    CV_Assert(idx>=0);
    CV_Assert(idx<n_bins);
    float value = 0.0;
    // TODO
    // Remember: Map integer range [0, n_bins) into float 
    // range [min_value, max_value)
    //este lo que hace es un rango de los enteros de 0 al rango dando
    //y devuelve un rango de valores desde el minimo al maximo
    value = min_value + (max_value - min_value) * static_cast<float>(idx) / static_cast<float>(n_bins);
    //
    CV_Assert(value >= min_value);
    CV_Assert(value < max_value);
    return value;
}

void 
fsiv_percentile_edge_detector(cv::Mat const& gradient, cv::Mat& edges,
    float th, int n_bins)
{
    CV_Assert(gradient.type()==CV_32FC1);

    // TODO
    // Remember: user other fsiv_xxx to compute histogram and percentiles.
    
    // Remember: map histogram range {0, ..., n_bins} to the gradient range 
    // {0.0, ..., max_grad}
    
    // Hint: use "operator >=" to threshold the gradient magnitude image.
    cv::Mat hist;
    float max_gradient;
    fsiv_compute_gradient_histogram(gradient, n_bins, hist, max_gradient);

    int idx = fsiv_compute_histogram_percentile(hist, th);

    float threshold_value = fsiv_histogram_idx_to_value(idx, n_bins, max_gradient);

    cv::Mat resul = gradient >= threshold_value;
    edges = resul * 255;
    //
    CV_Assert(edges.type()==CV_8UC1);
    CV_Assert(edges.size()==gradient.size());
}

void 
fsiv_otsu_edge_detector(cv::Mat const& gradient, cv::Mat& edges)
{
    CV_Assert(gradient.type()==CV_32FC1);

    // TODO
    // Hint: normalize input gradient into rango (0, 255) to use 
    // cv::threshold properly.
    //
    cv::Mat gradient_norm;
    cv::normalize(gradient, gradient_norm, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::threshold(gradient_norm, edges, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    //
    CV_Assert(edges.type()==CV_8UC1);
    CV_Assert(edges.size()==gradient.size());
}

void
fsiv_canny_edge_detector(cv::Mat const& dx, cv::Mat const& dy, cv::Mat& edges,
    float th1, float th2, int n_bins)
{
    CV_Assert(dx.size()==dy.size());
    CV_Assert(th1<th2);

    // TODO
    // Hint: convert the intput derivatives to CV_16C1 to be used with canny.
    // Remember: th1 and th2 are given as percentiles so you must transform to
    // gradient range to be used in canny method.
    // Remember: we compute gradients with L2_NORM so we must indicate this in
    // the canny method too.
    
    float max_gradient;
    cv::Mat gradient, hist;
    fsiv_compute_gradient_magnitude(dx, dy, gradient);
    fsiv_compute_gradient_histogram(gradient, n_bins, hist, max_gradient);


    int percentile_th1 = fsiv_compute_histogram_percentile(hist, th1);
    int percentile_th2 = fsiv_compute_histogram_percentile(hist, th2);

    // Calcular los valores de th1_value y th2_value usando la función fsiv_histogram_idx_to_value.
    double th1_value =  fsiv_histogram_idx_to_value(percentile_th1, n_bins, max_gradient);
    double th2_value = fsiv_histogram_idx_to_value(percentile_th2, n_bins, max_gradient);
    cv::Mat dx_tofloat, dy_tofloat;
    dx.convertTo(dx_tofloat, CV_16SC1);
    dy.convertTo(dy_tofloat, CV_16SC1);
    
    cv::Canny(dx_tofloat, dy_tofloat, edges, th1_value, th2_value, true);


    //
    CV_Assert(edges.type()==CV_8UC1);
    CV_Assert(edges.size()==dx.size());
}

void
fsiv_compute_confusion_matrix(cv::Mat const& gt, cv::Mat const& pred, cv::Mat & cm)
{
    CV_Assert(gt.type()==CV_8UC1);
    CV_Assert(pred.type()==CV_8UC1);
    CV_Assert(gt.size()==pred.size());

    // TODO
    // Remember: a edge detector confusion matrix is a 2x2 matrix where the 
    // rows are ground truth {Positive: "is edge", Negative: "is not edge"} and
    // the columns are the predictions labels {"is edge", "is not edge"}
    // A pixel value means edge if it is <> 0, else is a "not edge" pixel.

    cm = cv::Mat::zeros(2, 2, CV_32FC1);
    for (int i = 0; i < gt.rows; ++i) {
        for (int j = 0; j < gt.cols; ++j) {
            if (gt.at<uchar>(i, j) != 0) {
                if (pred.at<uchar>(i, j) != 0) {
                    cm.at<float>(0, 0) += 1;
                }
                else {
                    cm.at<float>(0, 1) += 1;
                }
            }
            else {
                if (pred.at<uchar>(i, j) != 0) {
                    cm.at<float>(1, 0) += 1;
                }
                else {
                    cm.at<float>(1, 1) += 1;
                }
            }
        }
    }

    //
    CV_Assert(cm.type()==CV_32FC1);
    CV_Assert(cv::abs(cv::sum(cm)[0]-(gt.rows*gt.cols))<1.0e-6);
}

float
fsiv_compute_sensitivity(cv::Mat const& cm)
{
    CV_Assert(cm.type()==CV_32FC1);
    CV_Assert(cm.size()==cv::Size(2,2));
    float sensitivity=0.0;
    // TODO    
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    sensitivity = cm.at<float>(0, 0) / (cm.at<float>(0, 0) + cm.at<float>(0, 1));
    //
    return sensitivity;
}

float
fsiv_compute_precision(cv::Mat const& cm)
{
    CV_Assert(cm.type()==CV_32FC1);
    CV_Assert(cm.size()==cv::Size(2,2));
    float precision=0.0;
    // TODO    
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    precision = cm.at<float>(0, 0) / (cm.at<float>(0, 0) + cm.at<float>(1, 0));
    //
    return precision;
}

float
fsiv_compute_F1_score(cv::Mat const& cm)
{
    CV_Assert(cm.type()==CV_32FC1);
    CV_Assert(cm.size()==cv::Size(2,2));
    float F1 = 0.0;
    // TODO
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    F1 = 2 * (fsiv_compute_precision(cm) * fsiv_compute_sensitivity(cm)) / (fsiv_compute_precision(cm) + fsiv_compute_sensitivity(cm));
    //
    return F1;
}

