cmake_minimum_required(VERSION 3.30)
project(montgomeryAlgorithms)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        include/app
)

add_executable(montgomeryAlgorithms
        src/main.cpp
        src/app/PrepareMon.cpp
        src/app/BinaryHelper.cpp
        src/app/CihsMethod.cpp
        src/app/FipsMethod.cpp
        src/app/int128Conversions.cpp
        src/app/RandomNumbersGenerator.cpp
        src/app/BasicMontgomery.cpp
)
