cmake_minimum_required(VERSION 3.11)
project(Fit LANGUAGES CUDA CXX)

set(CMAKE_CUDA_SEPARABLE_COMPILATION ON) # effective when created

add_library(saxpy STATIC functions.cu)

add_library(executor STATIC executor.cu executor2.cu)
target_link_libraries(executor PRIVATE saxpy)

add_executable(Fit)
target_sources(Fit PRIVATE main.cc)

target_link_libraries(Fit PRIVATE executor)
