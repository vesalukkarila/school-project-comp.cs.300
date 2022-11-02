cmake_minimum_required(VERSION 3.5)

project(wk08weekexcercise LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(wk08weekexcercise main.cpp)

install(TARGETS wk08weekexcercise
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
