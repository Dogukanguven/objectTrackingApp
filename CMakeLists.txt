cmake_minimum_required(VERSION 3.23)
project(ObjectTracking)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(TrackingApp objectTracking.cpp)
target_link_libraries(TrackingApp ${OpenCV_LIBS})
