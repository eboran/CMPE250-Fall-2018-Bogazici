cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 main.cpp passenger.cpp passenger.h event.cpp event.h type.cpp type.h)