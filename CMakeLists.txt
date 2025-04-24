cmake_minimum_required(VERSION 3.30)
project(montgomeryAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        include/app
        include/app2
)

add_executable(montgomeryAlgorithms
        src/main.cpp
        src/app2/MontgomeryApp.cpp
        src/app2/MontProImpl.cpp
        src/app/PrepareMon.cpp
        src/app/MonPro.cpp
        src/app/ModExp.cpp
    )
