#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include "common_code.hpp"
#include <iostream>

std::vector<cv::Point3f>
fsiv_generate_3d_calibration_points(const cv::Size& board_size,
                                    float square_size)
{
    std::vector<cv::Point3f> ret_v;
    //TODO
    //Remenber: the first inner point has (1,1) in board coordinates.

    //Hay que calcular el numero de puntos que hay en lo largo y en lo ancho
    float height = board_size.height;    
    float width = board_size.width;

    for(int i = 1; i <= height; i++){
        for(int j = 1; j <= width; j++){
            //recorremos la matriz de uno en uno por altura y anchura. Los puntos son cada unas de las celdas multiplicadas
            //por el tamaño, por lo que tenemos cada unos de los cuadrador
            ret_v.push_back(cv::Point3f(j*square_size,i*square_size, 0));
        }
    }


    
    //
    CV_Assert(ret_v.size()==static_cast<size_t>(board_size.width*board_size.height));
    return ret_v;
}


bool
fsiv_find_chessboard_corners(const cv::Mat& img, const cv::Size &board_size,
                             std::vector<cv::Point2f>& corner_points,
                             const char * wname)
{
    CV_Assert(img.type()==CV_8UC3);
    bool was_found = false;
    //TODO
    was_found = cv::findChessboardCorners(img, board_size, corner_points);
    if(was_found){
        cv::Mat img2;
        img.copyTo(img2);
        //cambiamos la imagen a escala de grises
        cv::cvtColor(img, img2, cv::COLOR_BGR2GRAY);
        //ajustmos la precision a nivel sub-pixel
        cv::cornerSubPix(img2, corner_points, cv::Size(5,5), cv::Size(-1, -1), cv::TermCriteria());
    }
    //dibuja los puntos de la tabla de ajedrez
    cv::drawChessboardCorners(img, board_size, corner_points, was_found);
    //si no es nulo, es el nombre de la imagen
    if(wname){
        cv::imshow(wname, img);
    }

    //
    return was_found;
}

float
fsiv_calibrate_camera(const std::vector<std::vector<cv::Point2f>>& _2d_points,
                      const std::vector<std::vector<cv::Point3f>>& _3d_points,
                      const cv::Size &camera_size,
                      cv::Mat& camera_matrix,
                      cv::Mat& dist_coeffs,
                      std::vector<cv::Mat>* rvecs,
                      std::vector<cv::Mat>* tvecs)
{
    CV_Assert(_3d_points.size()>=2 && _3d_points.size()==_2d_points.size());
    float error=0.0;
    //TODO
    std::vector<cv::Mat>r, t;
    //en el caso en el que algun vector venga apuntando a nulo, hay que
    //reservarle memoria para no pasar un parametro vacio
    if(tvecs == nullptr){
        tvecs = &t;
    }
    if(rvecs == nullptr){
        rvecs = &r;
    }
    error = cv::calibrateCamera(_3d_points, _2d_points, camera_size, camera_matrix, dist_coeffs, *rvecs, *tvecs);
    //
    CV_Assert(camera_matrix.rows==camera_matrix.cols &&
              camera_matrix.rows == 3 &&
              camera_matrix.type()==CV_64FC1);
    CV_Assert((dist_coeffs.rows*dist_coeffs.cols) == 5 &&
              dist_coeffs.type()==CV_64FC1);
    CV_Assert(rvecs==nullptr || rvecs->size()==_2d_points.size());
    CV_Assert(tvecs==nullptr || tvecs->size()==_2d_points.size());
    return error;
}

void fsiv_compute_camera_pose(const std::vector<cv::Point3f> &_3dpoints,
                              const std::vector<cv::Point2f> &_2dpoints,
                              const cv::Mat& camera_matrix,
                              const cv::Mat& dist_coeffs,
                              cv::Mat& rvec,
                              cv::Mat& tvec)
{
    CV_Assert(_3dpoints.size()>=4 && _3dpoints.size()==_2dpoints.size());
    //TODO
    cv::solvePnP(_3dpoints, _2dpoints, camera_matrix, dist_coeffs, rvec, tvec);
    //
    CV_Assert(rvec.rows==3 && rvec.cols==1 && rvec.type()==CV_64FC1);
    CV_Assert(tvec.rows==3 && tvec.cols==1 && tvec.type()==CV_64FC1);
}

void
fsiv_draw_axes(cv::Mat& img,               
               const cv::Mat& camera_matrix, const cv::Mat& dist_coeffs,
               const cv::Mat& rvec, const cv::Mat& tvec,
               const float size, const int line_width)
{
    //TODO
    std::vector<cv::Point2f> p2D;
    std::vector<cv::Point3f> p3D;
    p3D.push_back(cv::Point3f(0, 0, 0));
    p3D.push_back(cv::Point3f(size, 0, 0));
    p3D.push_back(cv::Point3f(0, size, 0));
    p3D.push_back(cv::Point3f(0, 0, -size));
    //tenemos un vector con los tres puntos en el plano 3D
    //hay que proyectarlos en el plano 2D
    cv::projectPoints(p3D, rvec, tvec, camera_matrix, dist_coeffs, p2D);
    //con line, me permite crear tres lineas rectas que pasen por los puntos que indico
    cv::line(img, p2D[0], p2D[1], cv::Scalar(0, 0, 255), line_width);
    cv::line(img, p2D[0], p2D[2], cv::Scalar(0, 255, 0), line_width);
    cv::line(img, p2D[0], p2D[3], cv::Scalar(255, 0, 0), line_width);

    //
}

void
fsiv_save_calibration_parameters(cv::FileStorage& fs,
                                const cv::Size & camera_size,
                                float error,
                                const cv::Mat& camera_matrix,
                                const cv::Mat& dist_coeffs,
                                 const cv::Mat& rvec,
                                 const cv::Mat& tvec)
{
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type()==CV_64FC1 && camera_matrix.rows==3 && camera_matrix.cols==3);
    CV_Assert(dist_coeffs.type()==CV_64FC1 && dist_coeffs.rows==1 && dist_coeffs.cols==5);
    CV_Assert(rvec.type()==CV_64FC1 && rvec.rows==3 && rvec.cols==1);
    CV_Assert(tvec.type()==CV_64FC1 && tvec.rows==3 && tvec.cols==1);
    //TODO
    fs << "image-width" << camera_size.width;
    fs << "image-height" << camera_size.height;
    fs << "error" << error;
    fs << "camera-matrix" << camera_matrix;
    fs << "distortion-coefficients" << dist_coeffs;
    fs << "rvec" << rvec;
    fs << "tvec" << tvec;
    //
    CV_Assert(fs.isOpened());
    return;
}

void
fsiv_load_calibration_parameters(cv::FileStorage &fs,
                                 cv::Size &camera_size,
                                 float& error,
                                 cv::Mat& camera_matrix,
                                 cv::Mat& dist_coeffs,
                                 cv::Mat& rvec,
                                 cv::Mat& tvec)
{
    CV_Assert(fs.isOpened());
    //TODO
    fs["image-width"] >> camera_size.width;
    fs["image-height"] >> camera_size.height;
    fs["error"] >> error;
    fs["camera-matrix"] >> camera_matrix;
    fs["distortion-coefficients"] >> dist_coeffs;
    fs["rvec"] >> rvec;
    fs["tvec"] >> tvec;
    //
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type()==CV_64FC1 && camera_matrix.rows==3 && camera_matrix.cols==3);
    CV_Assert(dist_coeffs.type()==CV_64FC1 && dist_coeffs.rows==1 && dist_coeffs.cols==5);
    CV_Assert(rvec.type()==CV_64FC1 && rvec.rows==3 && rvec.cols==1);
    CV_Assert(tvec.type()==CV_64FC1 && tvec.rows==3 && tvec.cols==1);
    return;
}

void
fsiv_undistort_image(const cv::Mat& input, cv::Mat& output,
                     const cv::Mat& camera_matrix,
                     const cv::Mat& dist_coeffs)
{
    //TODO
    //Hint: use cv::undistort.
    output = input.clone();
    cv::undistort(input, output, camera_matrix, dist_coeffs);
    //
}

void
fsiv_undistort_video_stream(cv::VideoCapture&input_stream,
                            cv::VideoWriter& output_stream,
                            const cv::Mat& camera_matrix,
                            const cv::Mat& dist_coeffs,
                            const int interp,
                            const char * input_wname,
                            const char * output_wname,
                            double fps)
{
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
    //TODO
    //Hint: to speed up, first compute the transformation maps
    //(one time only at the beginning using cv::initUndistortRectifyMap)
    // and then only remap (cv::remap) the input frame with the computed maps.
    cv::Mat undistorted_map1, undistorted_map2, input_image, output_image, undistorted_frame;
    double delay_time = 1000.0 / fps;
    int input_key = 0;

    cv::initUndistortRectifyMap(camera_matrix, dist_coeffs, undistorted_frame, camera_matrix, 
        input_image.size(), CV_32FC1, undistorted_map1, undistorted_map2);
    

    while (input_key != 27 && !input_image.empty()) {
        cv::remap(input_image, undistorted_frame, undistorted_map1, undistorted_map2, interp);

        if (input_wname != nullptr) {
            cv::imshow(input_wname, input_image);
        }
        if (output_wname != nullptr) {
            cv::imshow(output_wname, undistorted_frame);
        }

        input_stream >> input_image;
        output_stream.write(undistorted_frame);
        
        input_key = cv::waitKey(delay_time);
    }

    //
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
}
