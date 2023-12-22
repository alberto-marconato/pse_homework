# Make an aoutomatic library - will be static or dynamic based on user settings
add_library(boid SHARED boid.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(boid PUBLIC ../include)