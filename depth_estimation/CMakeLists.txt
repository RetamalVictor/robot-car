cmake_minimum_required(VERSION 3.0)

project(YOLOv5s)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(YOLOv5s yolo.cpp)

target_link_libraries(YOLOv5s ${OpenCV_LIBS})
