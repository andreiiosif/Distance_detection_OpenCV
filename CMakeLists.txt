cmake_minimum_required(VERSION 3.23)
project(Image_Processing_Template) # Be sure to use the correct project name, in this case "match test" is my personal one !

set(CMAKE_CXX_STANDARD 14) # If you wanna change the language standard
set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build") # And yes do not forget to change the path !
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Image_Processing_Template main.cpp DisplayVideo.cpp DisplayVideo.h) # Change "match test"

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(Image_Processing_Template ${OpenCV_LIBS}) # Like I said be sure to properly rename the project name !
