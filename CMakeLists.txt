cmake_minimum_required (VERSION 2.8.8)
project (dn_detector)

add_definitions(-DCUDNN)
add_definitions(-DOPENCV)
add_definitions(-DGPU)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -W ")

set(CMAKE_BUILD_TYPE Release)

add_library(darknet INTERFACE)
set(Darknet_INCLUDE_DIR
        /usr/local/darknet/include/
        /usr/local/cuda/include/
        )
set(Darknet_LIBRARIES
        /usr/local/darknet/lib/libdarknet.a
        -lpthread
        -lgomp
        -lcuda
        -lcudart
        -lcublas
        -lcurand
        -lcudnn
        -L/usr/local/cuda/lib64
        )
target_include_directories(darknet INTERFACE ${Darknet_INCLUDE_DIR})
target_link_libraries(darknet INTERFACE ${Darknet_LIBRARIES})
message(STATUS "Darknet library status:")
message(STATUS "    Darknet_INCLUDE_DIR: ${Darknet_INCLUDE_DIR}")
message(STATUS "    Darknet_LIBRARIES: ${Darknet_LIBRARIES}")


set(CMAKE_PREFIX_PATH "/usr/local/opencv/share/OpenCV")
find_package(OpenCV 3.4.2 REQUIRED) # find_package(OpenCV 3.1.0  EXACT REQUIRED)
add_library(opencv INTERFACE)
target_include_directories(opencv INTERFACE ${OpenCV_INCLUDE_DIRS})
list(REMOVE_ITEM OpenCV_LIBS opencv_dnn) # remove caffe libs
list(REMOVE_ITEM OpenCV_LIBS opencv_hdf) # remove hdf5 libs
target_link_libraries(opencv INTERFACE ${OpenCV_LIBS})
message(STATUS "OpenCV library status:")
message(STATUS "    OPENCV_ROOT_DIR: ${OPENCV_ROOT_DIR}")
message(STATUS "    OpenCV_VERSION: ${OpenCV_VERSION}")
message(STATUS "    OpenCV_LIBS: ${OpenCV_LIBS}")
message(STATUS "    OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

add_executable(dn_example
        src/dn_detector.cpp
        src/main.cpp
        )
target_include_directories(dn_example PUBLIC
        include
        )
target_link_libraries(dn_example PUBLIC
        darknet
        opencv
        )