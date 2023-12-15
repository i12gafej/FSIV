/*!
  READ AND SHOW DATASET.

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

static const int LEFT_ARROW = 81;
static const int RIGHT_ARROW = 83;


int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {
      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Load the fashion mnist dataset (binary format). "
                   "You can download it from Moodle");
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
      fsiv_load_dataset(folder, 0, X, y);
      
      const int dataset_size = X.rows;
      std::cout << "Loaded " << dataset_size << " images." << std::endl;
      
      int key = 0;
      int idx = 0;
      std::string wname = "IMAGE";
      cv::namedWindow(wname, cv::WINDOW_GUI_EXPANDED);
      cv::resizeWindow(wname, cv::Size(256,256));
      do
      {   
          // TODO: Get sample with current 'idx' and assign it to 'img'
          
          std::string nombre_imagen = fsiv_get_dataset_label_name(idx);
          cv::Mat img;
          // TODO: show the current image
          // ...
            img = cv::imread(nombre_imagen);
            cv::imshow ("IMG", img);
          
          //TODO: display its label
          std::cout << "Idx " << idx << ": "; // TODO continue cout                    
                    //TODO: use fsiv_get_dataset_label_name() :: you may need this conversion 'std::uint32_t'
          fsiv_get_dataset_label_name

          key = cv::waitKey(0) & 0xff;
          
          if (key == LEFT_ARROW)
              idx = (idx-1+dataset_size) % dataset_size;
          else if  (key == RIGHT_ARROW)
              idx = (idx+1) % dataset_size;
          else if (key != 27)
              std::cout << "Unknown keypress code '" << key
                        << "' [Press <-, ->, or ESC]." << std::endl;
      }
      while (key != 27);

      cv::destroyWindow(wname);
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
