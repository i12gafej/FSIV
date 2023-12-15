/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message.}"
    "{verbose        |      | activate verbose mode.}"
    "{i intrinsics   |      | Calibrate only extrinsics parameters. Using intrinsics from given file (-i=intr-file).}"
    "{s size         |<none>| square size.}"
    "{r rows         |<none>| number of board's rows.}"
    "{c cols         |<none>| number of board's cols.}"
    "{@output        |<none>| filename for output intrinsics file.}"
    "{@input1        |<none>| first board's view.}"
    "{@input2        |      | second board's view.}"
    "{@inputn        |      | ... n-idx board's view.}"
    ;

int
main (int argc, char* const* argv)
{
    int retCode=EXIT_SUCCESS;

    try {        
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Calibrate the intrinsics parameters of a camera.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        float square_size = parser.get<float>("s");
        int rows = parser.get<int>("r");
        int cols = parser.get<int>("c");
        bool verbose = parser.has("verbose");
        std::string output_fname = parser.get<cv::String>("@output");
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        //Get the inputs.
        //find the second argument without '-' at begin.
        int input = 1;
        bool found = false;
        while (input<argc && !found)
            found = argv[input++][0] != '-';
        CV_Assert(input<argc);
        std::vector<std::string> input_fnames;        
        for (; input<argc; ++input)
            input_fnames.push_back(std::string(argv[input]));

        //TODO
        cv::Mat entrada, matriz, coeffs, rvec, tvec;
        float error;
        std::vector<cv::Mat> rvecs, tvecs;

        std::vector<cv::Point3f> p3D;
        std::vector<cv::Point2f> p2D;

        std::vector<std::vector<cv::Point3f>> wcs_axis;
        std::vector<std::vector<cv::Point2f>> c_points;


        
        
        cv::FileStorage fs;
        cv::Size tamano_tabla(cols-1, rows-1), tamano_camara;
        cv::namedWindow("INPUT");
        cv::namedWindow("OUTPUT");

        std::string input_fname = parser.get<cv::String>("i");


        if (parser.has("i"))
        {
            //TODO
            fs.open(input_fname, cv::FileStorage::Mode::READ);
            fsiv_load_calibration_parameters(fs, tamano_camara, error, matriz, coeffs, rvec, tvec);
            entrada = cv::imread(input_fnames[0]);
            cv::imshow ("INPUT", entrada);
            fsiv_find_chessboard_corners(entrada, tamano_tabla, p2D, "OUTPUT");
            p3D = fsiv_generate_3d_calibration_points(tamano_tabla, square_size);
            fsiv_compute_camera_pose(p3D, p2D, matriz, coeffs, rvec, tvec);
            fs.open(output_fname, cv::FileStorage::Mode::WRITE);
            fsiv_save_calibration_parameters(fs, tamano_camara, error, matriz, coeffs, rvec, tvec);
            




            //
            if (verbose)
            {
                //TODO
                
                fsiv_draw_axes(entrada, matriz, coeffs, rvec, tvec, 0.1);
                cv::imshow ("OUTPUT", entrada);

                //
            }
        }
        else
        {
            //TODO
            p3D = fsiv_generate_3d_calibration_points(tamano_tabla, square_size);



            for(int i = 0; i < (int)input_fnames.size(); i++){
                entrada = cv::imread(input_fnames[i]);
                cv::imshow ("INPUT", entrada);

                bool was_found = fsiv_find_chessboard_corners(entrada, tamano_tabla, p2D, "OUTPUT");
                if(was_found){
                    wcs_axis.push_back(p3D);
                    c_points.push_back(p2D);
                }
            }
            error = fsiv_calibrate_camera(c_points, wcs_axis, entrada.size(), matriz, coeffs, &rvecs, &tvecs);
            //

            if (verbose)
            {
                //TODO
                for(int i = 0; i < (int)input_fnames.size(); i++){

                    entrada = cv::imread(input_fnames[i]);
                    fsiv_draw_axes(entrada, matriz, coeffs, rvecs[i], tvecs[i], 0.1);
                    cv::imshow ("OUTPUT", entrada);
                    int k = cv::waitKey(0)&0xff;
                }

                //
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
