//! \file chroma_key.cpp
//! Replace background based on color
//! University of Cordoba
//! (c) MJMJ/2020 FJMC/2022-

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "common_code.hpp"

const char * keys =
    "{help usage ? |      | print this message   }"
    "{h hue          |  60  | Chroma key (hue). Def. 60}"
    "{s sensitivity  |  20 | sensitivity. Def. 20}"
    "{v video        |     | the input is a videofile.}"
    "{c camera       |     | the input is a capture device index.}"
    "{@input         |<none>| input source (pathname or camera idx).}"
    "{@background    |<none>| pathname of background image.}"
    ;






int
main(int argc, char * argv[])
{
    int retCode = EXIT_SUCCESS;
    try {
        /// Init the parser
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Replace background based on color.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        // Get the values
        int hue = parser.get<int>("h");
        int sensitivity = parser.get<int>("s");
        std::string inputSource = parser.get<cv::String>(0);
        std::string backgroundPath = parser.get<cv::String>(1);

        //

        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        //DO the work!!.
        cv::Mat input, background, output;
        input = cv::imread(inputSource);
        if (input.empty()) {
          std::cerr << "Error: could not open the input image file '" << input_name << "'." << std::endl;
          return EXIT_FAILURE;
      }
        // Load input image or video frame
        /*if (parser.has("v")) {
            // Code for loading video input
            // cv::VideoCapture cap(inputSource);
            // while (cap.isOpened()) {
            //     cap >> input;
            //     // Process input frame here
            // }
        } else if (parser.has("c")) {
            // Code for loading input from camera
            // cv::VideoCapture cap(parser.get<int>("c"));
            // while (cap.isOpened()) {
            //     cap >> input;
            //     // Process input frame here
            // }
        } else {
            // Load input image
            
        }*/

        // Load background image
        background = cv::imread(backgroundPath);

        // Apply chroma keying
        output = fsiv_apply_chroma_key(input, background, hue, sensitivity);

        // Show or save the output image
        cv::imshow("Output", output);
        cv::waitKey(0);
        cv::imwrite("output.jpg", output);




    }
    catch (std::exception& e)
    {
        std::cerr << "Excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown excepcion." << std::endl;
        retCode = EXIT_FAILURE;
    }

    return retCode;
}