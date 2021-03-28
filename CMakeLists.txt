cmake_minimum_required(VERSION 3.15)

# Silence warnings about empty CUDA_ARCHITECTURES properties on example targets:
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.18)
  cmake_policy(SET CMP0104 OLD)
endif()

project(Fit)

add_subdirectory(extern/NVIDIA/thrust)

include(extern/GooStats/cmake-utilities/INITIALIZE_CUDA.cmake)
INITIALIZE_CUDA()

add_library(Fit-devicelib INTERFACE)
target_link_libraries(Fit-devicelib INTERFACE MyThrust)

add_library(saxpy STATIC functions.cu)
target_link_libraries(saxpy PUBLIC Fit-devicelib)
add_library(executor STATIC executor.cu)
target_link_libraries(executor PUBLIC saxpy)
add_library(executor2 STATIC executor2.cu)
target_link_libraries(executor2 PUBLIC saxpy)

add_library(Fit-lib INTERFACE)
target_link_libraries(Fit-lib INTERFACE executor executor2)
target_include_directories(Fit-lib INTERFACE ${PROJECT_SOURCE_DIR})

add_executable(Fit main.cc)
target_link_libraries(Fit PRIVATE Fit-lib)

# test
add_subdirectory(extern/google/googletest/googletest)
enable_testing()
add_subdirectory(tests)
