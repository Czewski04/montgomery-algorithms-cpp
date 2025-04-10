cmake_minimum_required(VERSION 3.30)
project(montgomeryAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        include/app
)

add_executable(montgomeryAlgorithms
        src/main.cpp
        src/app/MontgomeryApp.cpp
        src/app/MontProImpl.cpp
    )
