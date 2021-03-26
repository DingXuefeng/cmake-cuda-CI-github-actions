cmake_minimum_required(VERSION 3.11)
project(Fit LANGUAGES CUDA CXX)

set(CMAKE_CUDA_SEPARABLE_COMPILATION ON) # effective when created

add_library(saxpy STATIC functions.cu)

add_library(executor STATIC executor.cu executor2.cu)
target_link_libraries(executor PRIVATE saxpy)

add_library(Fit-lib INTERFACE)
target_link_libraries(Fit-lib INTERFACE executor)

add_executable(Fit)
target_sources(Fit PRIVATE main.cc)

target_link_libraries(Fit PRIVATE Fit-lib)

ExternalProject_Add(
    gtest
    URL http://googletest.googlecode.com/files/gtest-1.10.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    URL_MD5 82358affdd7ab94854c8ee73a180fc53
    INSTALL_COMMAND ""
)

# test
ExternalProject_Get_Property(gtest source_dir binary_dir)
add_library(libgtest INTERFACE)
add_dependencies(libgtest gtest)
target_link_libraries(libgtest
    INTERFACE Threads::Threads
              "${binary_dir}/libgtest_main.a"
              "${binary_dir}/libgtest.a")
target_include_directories(libgtest INTERFACE "${source_dir}/include")
enable_testing()
add_subdirectory(tests)
