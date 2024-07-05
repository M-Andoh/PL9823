cmake_minimum_required(VERSION 3.13)

add_library(color STATIC
  color.cpp
)

target_link_libraries(color PUBLIC 
    pico_stdlib)

# Add the standard include files to the build
target_include_directories(color PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
