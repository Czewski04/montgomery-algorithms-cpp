cmake_minimum_required(VERSION 3.30)
project(montgomeryAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        include/app
)

add_executable(montgomeryAlgorithms
        src/main.cpp
        src/app/PrepareMon.cpp
        src/app/MonPro.cpp
        src/app/ModExp.cpp
        src/app/BinaryHelper.cpp
        src/app/CihsMethod.cpp
        src/app/FipsMethod.cpp
    )
