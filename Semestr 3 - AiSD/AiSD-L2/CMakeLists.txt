cmake_minimum_required(VERSION 3.17)
project(AiSD-L2)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)
file(GLOB SOURCES inc/*.hpp inc/*.cpp)

add_executable(AiSD-L2 main.cpp ${SOURCES})
