cmake_minimum_required(VERSION 3.22.0)
project(EvaSecurity VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "v")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/EvaSys")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(EvaSecurity 
    src/main.cpp
    src/Header/Camera.h
    src/Camera.cpp
    src/Header/FileManagment.h
    src/FileManager.cpp
    src/Header/Detector.h
    src/Detector.cpp
    )

target_link_libraries(EvaSecurity ${OpenCV_LIBS})


