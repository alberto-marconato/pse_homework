add_executable(main main.cpp)

target_link_libraries(main PRIVATE boid)
target_link_libraries(main PRIVATE reynold)
target_link_libraries(main PRIVATE pthread)