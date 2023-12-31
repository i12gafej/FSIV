CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(fashion_mnist_lite)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

set(WITH_OPENMP OFF CACHE BOOL "Use openmp for pararell processing.")
if (WITH_OPENMP)
  find_package(OpenMP REQUIRED)
  if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    add_definitions(-DUSE_OPENMP)
  endif(OPENMP_FOUND)
endif (WITH_OPENMP)

add_library(common_code STATIC 
    dataset.cpp dataset.hpp        
    #Add your feature extractors modules here
    )

add_executable(show_fashion_mnist show_fashion_mnist.cpp)
target_link_libraries(show_fashion_mnist common_code)
