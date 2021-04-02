cmake_minimum_required(VERSION 2.8)

project(physarumgen)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} )
add_executable(physarumgen main.cpp)
target_link_libraries(physarumgen ${OpenCV_LIBS})