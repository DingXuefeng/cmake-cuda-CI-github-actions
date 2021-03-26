cmake_minimum_required(VERSION 3.11)
project(Fit LANGUAGES CUDA CXX)

set(CMAKE_CUDA_SEPARABLE_COMPILATION ON) # effective when created

add_library(saxpy STATIC functions.cu)

add_library(executor STATIC executor.cu executor2.cu)
target_link_libraries(executor PRIVATE saxpy)

add_library(Fit-lib INTERFACE)
target_link_libraries(Fit-lib INTERFACE executor)
target_include_directories(Fit-lib INTERFACE ${PROJECT_SOURCE_DIR})

add_executable(Fit)
target_sources(Fit PRIVATE main.cc)

target_link_libraries(Fit PRIVATE Fit-lib)

# test
include(FetchContent)

FetchContent_Declare(
  googletest  
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)
