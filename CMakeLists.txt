cmake_minimum_required(VERSION 3.10.2)

project(Homework
        DESCRIPTION "Simulate a group of boid objects"
        VERSION  0.1
        LANGUAGES CXX)

# The compiled library code is here
add_subdirectory(libs)

# The executable code is here
add_subdirectory(src)
add_subdirectory(test)
