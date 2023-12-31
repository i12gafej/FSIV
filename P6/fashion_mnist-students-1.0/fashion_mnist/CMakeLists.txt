CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(fashion_mnist)
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

add_library(common_code STATIC common_code.hpp
    dataset.cpp dataset.hpp
    classifiers.cpp classifiers.hpp
    metrics.cpp metrics.hpp
    features.cpp features.hpp
    gray_levels_features.hpp gray_levels_features.cpp
    histogram_features.hpp histogram_features.cpp
    local_binary_pattern_features.hpp local_binary_pattern_features.cpp
    #Add your feature extractors modules here    
    )

add_executable(test_common_code test_common_code.cpp)
target_link_libraries(test_common_code common_code)

add_executable(show_fashion_mnist show_fashion_mnist.cpp)
target_link_libraries(show_fashion_mnist common_code)

add_executable(train_clf train_clf.cpp)
target_link_libraries(train_clf common_code)

add_executable(test_clf test_clf.cpp)
target_link_libraries(test_clf common_code)
