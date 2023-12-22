cmake_minimum_required(VERSION 3.10.2)

project(homework
        DESCRIPTION "Simulate a group of boid objects"
        VERSION  0.1
        LANGUAGES CXX)

#Generate the shared libraries from the sources
add_library(boid STATIC libs/boid.cpp)

#Bring the headers into the project
target_include_directories(boid PUBLIC include)