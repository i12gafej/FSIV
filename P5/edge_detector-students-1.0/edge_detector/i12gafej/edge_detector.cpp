#include <iostream>
#include <exception>

//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const char * keys =
    "{help h usage ? |      | print this message   }"
    "{i              |      | Activate interactive mode.}"
    "{s_ap           | 1    | Sobel kernel aperture radio: 0, 1, 2, 3}"
    "{n_bins         | 100  | Gradient histogram size}"
    "{g_r            | 1    | radius of gaussian filter (2r+1). Value 0 means don't filter.}"
    "{th             | 0.8  | Gradient percentile used as threshold for the gradient percentile detector (th2 for canny).}"
    "{th1            | 0.2  | Gradient percentile used as th1 threshold for the Canny detector (th1 < th).}"
    "{m method       | 0    | Detector used: 0:percentile detector, 1:Otsu detector, 2:canny detector}"
    "{c consensus    | 0    | If a ground truth was given, use greater to c% consensus to generate ground truth.}"
    "{@input         |<none>| input image.}"
    "{@output        |<none>| output image.}"
    "{@ground_truth  |      | optional ground truth image to compute the detector metrics.}"
    ;

//./edge_detector -s_ap=1 -n_bins=100 -g_r=1 -th=0.8 -th1=0.2 -m=0 -c=0 ../data/8068.jpg out.jpg

int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Edge detector v0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      cv::String input_fname = parser.get<cv::String>("@input");
      cv::String output_fname = parser.get<cv::String>("@output");
      cv::String gt_fname = parser.get<cv::String>("@ground_truth");
      int n_bins = parser.get<int>("n_bins");
      int g_r = parser.get<int>("g_r");
      float th2 = parser.get<float>("th");
      float th1 = parser.get<float>("th1");
      int s_ap = parser.get<int>("s_ap");
      int method = parser.get<int>("method");
      float consensus = parser.get<float>("c");
      bool interactive = parser.has("i");

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    cv::Mat img = cv::imread(input_fname, cv::IMREAD_GRAYSCALE);    
    cv::Mat gt_img;
    if (gt_fname != "")
      gt_img = cv::imread(gt_fname, cv::IMREAD_GRAYSCALE);

    // TODO
    // Remember: you must threshold gt image (>consensus) to get a 0/255 ground-truth.        
     if (!gt_img.empty()) {
            cv::threshold(gt_img, gt_img, consensus * 255, 255, cv::THRESH_BINARY);
        }

        cv::Mat dx, dy, gradient, edges;

        // Compute derivatives
        fsiv_compute_derivate(img, dx, dy, g_r, s_ap);
        // Compute gradient magnitude
        fsiv_compute_gradient_magnitude(dx, dy, gradient);
        

        // Choose edge detection method
        if (method == 0) {
            fsiv_percentile_edge_detector(gradient, edges, th2, n_bins);
        } else if (method == 1) {
            fsiv_otsu_edge_detector(gradient, edges);
        } else if (method == 2) {
            fsiv_canny_edge_detector(dx, dy, edges, th1, th2, n_bins);
        }

        cv::namedWindow("Edges", cv::WINDOW_NORMAL);
        cv::namedWindow("Original", cv::WINDOW_NORMAL);
        cv::namedWindow("Gt", cv::WINDOW_NORMAL);
        
                
        // Compare with ground truth
        if (!gt_img.empty()) {
            cv::imshow("Gt", gt_img);
            cv::Mat confusion_matrix;
            fsiv_compute_confusion_matrix(gt_img, edges, confusion_matrix);

            float sensitivity = fsiv_compute_sensitivity(confusion_matrix);
            float precision = fsiv_compute_precision(confusion_matrix);
            float f1_score = fsiv_compute_F1_score(confusion_matrix);

            std::cout << "Sensitivity: " << sensitivity << std::endl;
            std::cout << "Precision: " << precision << std::endl;
            std::cout << "F1 Score: " << f1_score << std::endl;
        }
        int key = 0;
        // Save or display result
        if (!output_fname.empty() && !interactive) {
            cv::imwrite(output_fname, edges);
            cv::imshow("Original", img);
            cv::imshow("Edges", edges);
            cv::waitKey(0);
        } else if (interactive) {
            cv::imshow("Original", img);
            int scaledTh2 = static_cast<int>(th2 * 100.0);
            int scaledTh1 = static_cast<int>(th1 * 100.0);
            int r = 0;
            cv::createTrackbar("Threshold", "Edges", &scaledTh1, 100);
            cv::createTrackbar("Threshold 2", "Edges", &scaledTh2, 100);
            cv::createTrackbar("Gaussian radius", "Edges", &g_r, 10);
            cv::createTrackbar("Sobel aperture (val = 2r + 1)", "Edges", &r, 5);
            cv::createTrackbar("Method", "Edges", &method, 2);
            int scaledConsensus = static_cast<int>(consensus * 100.0);
            cv::createTrackbar("Consensus", "Edges", &scaledConsensus, 100);
            while(key != 27){
                if (!gt_img.empty()) {
                    cv::threshold(gt_img, gt_img, consensus * 255, 255, cv::THRESH_BINARY);
                }
                th2 = static_cast<float>(scaledTh2) / 100.0;
                th1 = static_cast<float>(scaledTh1) / 100.0;
                consensus = static_cast<float>(scaledConsensus) / 100.0;
                s_ap = 2*r + 1;
                cv::Mat dx, dy, gradient, edges;


                // Compute derivatives
                fsiv_compute_derivate(img, dx, dy, g_r, s_ap);
                // Compute gradient magnitude
                fsiv_compute_gradient_magnitude(dx, dy, gradient);
                

                // Choose edge detection method
                if (method == 0) {
                    fsiv_percentile_edge_detector(gradient, edges, th2, n_bins);
                } else if (method == 1) {
                    fsiv_otsu_edge_detector(gradient, edges);
                } else if (method == 2) {
                    fsiv_canny_edge_detector(dx, dy, edges, th1, th2, n_bins);
                }

                // Compare with ground truth
                if (!gt_img.empty()) {
                    cv::Mat confusion_matrix;
                    fsiv_compute_confusion_matrix(gt_img, edges, confusion_matrix);

                    float sensitivity = fsiv_compute_sensitivity(confusion_matrix);
                    float precision = fsiv_compute_precision(confusion_matrix);
                    float f1_score = fsiv_compute_F1_score(confusion_matrix);

                    std::cout << "Sensitivity: " << sensitivity << std::endl;
                    std::cout << "Precision: " << precision << std::endl;
                    std::cout << "F1 Score: " << f1_score << std::endl;
                }
                cv::imshow("Edges", edges);
                
                key = cv::waitKey(30);
            }
            //cv::imshow("Edges", edges);
            
        }

    //

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Capturada excepcion desconocida!" << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
