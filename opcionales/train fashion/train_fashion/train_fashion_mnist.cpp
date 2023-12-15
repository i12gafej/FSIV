/*!
  TRAIN A SIMPLE KNN CLASSIFIER.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <string>
#include <exception>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "dataset.hpp"

const char * keys =
    "{help h usage ? |      | print this message   }"
    "{@data          |./mnist/| folder with the dataset.}"
    ;


int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {
      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Load the fashion mnist dataset (binary format). "
                   "And train a simple KNN classifier.");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      std::string folder = parser.get<std::string>("@data");
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }
      
      std::cout << "Loading data from folder: " << folder << std::endl;
      
      cv::Mat X, y;
      //  TODO: call function fsiv_load_dataset()
      // ...
      fsiv_load_dataset(folder,0, X, y);



      const int dataset_size = X.rows;
      std::cout << "Loaded " << dataset_size << " images." << std::endl;

      // #TODO: images are 28x28 pix, but we need to convert them to 1D feature vectors
      // A possible descriptor is computing the mean of each row (or column) of the image
      // ...
      cv::Mat X_1d;
      for(int i = 0; i < X.rows; i++){
        cv::Mat row = X.row(i);
        cv::Mat row_1d;
        cv::reduce(row, row_1d, 1, cv::REDUCE_AVG);
        X_1d.push_back(row_1d);
      }
      
      // for(int i = 0; i < X.cols; i++){
      //   cv::Mat col = X.col(i);
      //   cv::Mat col_1d;
      //   cv::reduce(col, col_1d, 0, cv::REDUCE_AVG);
      //   X_1d.push_back(col_1d);
      // }

      
      X_1d.convertTo(X_1d, CV_32F);

      // #TODO: create the knn classifier with KNearest class
      // ...
      cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();


      // #TODO: train the classifier with the train method
      // ...
      knn->train(X_1d, cv::ml::ROW_SAMPLE, y);

      
      // #TODO: evaluate the classifier with the method 'findNearest'
      // ...
      cv::Mat y_pred;
      knn->findNearest(X_1d, 1, y_pred);
      
      
      
      y.convertTo(y, CV_32F);


      // #TODO: compute the accuracy
      // ...

      
      float valor = static_cast<float>(cv::countNonZero(y_pred - y)) / static_cast<float>(dataset_size);

      
      std::cout << "Accuracy: " << valor * 100<<" %" << std::endl;



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
