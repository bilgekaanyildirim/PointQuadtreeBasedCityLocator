cmake_minimum_required(VERSION 3.27)
project(PointQuadtreeBasedCityLocator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PointQuadtreeBasedCityLocator
        Quadtree.cpp
        Quadtree.h
        source.cpp)
