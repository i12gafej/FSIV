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

        /*cv::String input = parser.get<cv::String>("@input"); 
        cv::String background = parser.get<cv::String>("@background"); 
        int h = parser.get<int>("h"); 
        int s = parser.get<int>("s"); 
        std::string v = parser.get<std::string>("v"); 
        int c = parser.get<int>("c"); 
        //

        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }



        //DO the work!!.
        std::cout<<"UVEeeeeeeeeeeeeeeeeeeeee: "<<v<<std::endl;
        cv::VideoCapture captura;
        if (parser.has("v")){
            captura.open(v);
        }
          
        else if(parse.has("c")){
            //Para abrir un dispositvo opencv usa indices enteros.
            //para identificarlos. Usa -1 para abrir el primero disponible.
            captura.open(c);
        }
         

      
        if (!vid.isOpened())
        {
             std::cerr << "Error: no he podido abrir el la fuente de vídeo." << std::endl;
            return EXIT_FAILURE;
        }
        
      //Creo la ventana grafica para visualizar la imagen.
      //El nombre de la ventana sirve como 'handle' para gestionarla despues.
      //Lee la documentacon de namedWindow para mas detalles.

        if (parser.has("v")){
            cv::namedWindow("VIDEO");

            cv::Mat frame;

            vid >> frame;

            if (frame.empty())
            {
                std::cerr << "Error: could not capture any frame from source." << std::endl;
                return EXIT_FAILURE;
            }

            std::cout << "Input size (WxH): " << frame.cols << 'x' << frame.rows << std::endl;
            std::cout << "Frame rate (fps): " << vid.get(cv::CAP_PROP_FPS) << std::endl;
            std::cout << "Num of frames   : " << vid.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;

            //Coordenadas del pixel a muestrear.
             //Inicialmente muestrearemos el pixel central.
            int coords[2] = {frame.cols/2, frame.rows/2};
            cv::namedWindow("VIDEO");
            cv::setMouseCallback ("VIDEO", on_mouse, coords);
            std::cerr << "Pulsa una tecla para continuar (ESC para salir)." << std::endl;
            int key = cv::waitKey(0) & 0xff;
            
            //Muestro frames hasta fin del video (frame vacio),
            //o que el usario pulse la tecla ESCAPE (codigo ascci 27)
            while (!frame.empty() && key!=27)
            {
                //muestro el frame.
                cv::imshow("VIDEO", frame);
                
                //mostramos los valores RGB del pixel muestreado.
                const cv::Vec3b v = frame.at<cv::Vec3b>(coords[1], coords[0]);
                std::cout << "RGB point (" << coords[0] << ',' << coords[1] << "): "
                        << static_cast<int>(v[0]) << ", "
                        << static_cast<int>(v[1]) << ", "
                        << static_cast<int>(v[2]) << std::endl;

                //Espero un tiempo fijado. Si el usuario pulsa una tecla obtengo
                //el codigo ascci. Si pasa el tiempo, retorna -1.
                key = cv::waitKey(wait) & 0xff;
                
                //capturo el siguiente frame.
                vid >> frame;
            }
            //Destruir la ventana abierta.
            cv::destroyWindow("VIDEO");

        }
        else if(parse.has("c")){
        
        }
      
        */
      


      //Creamos la ventana para mostrar el video y
      //le conectamos una función "callback" para gestionar el raton.
      



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
