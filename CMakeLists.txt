cmake_minimum_required(VERSION 3.10.0)
project(EvaSecurity VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(EvaSecurity 
    src/main.cpp
    src/Header/Camera.h
    src/Camera.cpp
    src/Header/FileManagment.h
    src/FileManager.cpp
    )

target_link_libraries(EvaSecurity ${OpenCV_LIBS})


