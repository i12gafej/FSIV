#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat fsiv_toHomogeneous(Mat& in){
    Mat row = Mat::ones(1, in.cols, CV_32F);  // 3 cols, 1 row
    vconcat(in, row, in);                   // 3 cols, 5 rows
    return in;
}

Mat fsiv_pinholeMatrix(float fx, float fy, float cx, float cy){
    Mat matriz(3, 4, CV_32F);
      
    matriz.at<float>(0, 0) = fx;
    matriz.at<float>(0, 2) = cx;
    matriz.at<float>(1, 1) = fy;
    matriz.at<float>(1, 2) = cy;
    matriz.at<float>(2, 3) = 1.0;
    return matriz;
}

Mat fsiv_projectPoints(Mat& projected, Mat& points){
    Mat d;
    gemm(projected, points, 1.0, Mat(), 0.0, d);
    return d;
}
int main(){
    Mat A = fsiv_pinholeMatrix(4.0, 7.0, 2.0, 5.0);
    cout << "A:       "<<A <<endl;
    Mat B(3, 1, CV_32F);
    B.at<float>(0,0) = 7.0;
    B.at<float>(0,1) = 2.0;
    B.at<float>(0,2) = 3.0;
    cout<< "B:       "<<B <<endl;
    Mat Bp = fsiv_toHomogeneous(B);
    cout<< "B Homogenea:        "<<Bp <<endl;
    Mat C = fsiv_projectPoints(A, Bp);
    //  Mat matrizExistente = (Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    // cout << "Matriz existente:" << endl << matrizExistente << endl;

    // // Crear una nueva fila para añadir
    // Mat nuevaFila = (Mat_<float>(1, 3) << 10, 11, 12);

    // // Añadir la nueva fila a la matriz existente
    // vconcat(matrizExistente, nuevaFila, matrizExistente);

    // // Mostrar la matriz después de añadir la fila
    // cout << "Matriz después de añadir una fila:" << endl << matrizExistente << std::endl;

    
    
    cout <<"C     : "<< C <<endl;
    cout<< "Los puntos son: "<<endl;
    cout << C.at<float>(0,0)/B.at<float>(0,2)<<endl;
    cout << C.at<float>(1,0)/B.at<float>(0,2)<<endl;

}