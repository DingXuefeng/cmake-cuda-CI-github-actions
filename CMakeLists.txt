cmake_minimum_required(VERSION 3.15)

# Silence warnings about empty CUDA_ARCHITECTURES properties on example targets:
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.18)
  cmake_policy(SET CMP0104 OLD)
endif()

project(Fit)

### include utilities
include(FetchContent)

### select host & device ###
set(DEVICE_LISTING CUDA OMP CPP TBB Auto)
set(HOST_LISTING OMP CPP TBB Auto)
mark_as_advanced(DEVICE_LISTING HOST_LISTING)
set(DEVICE Auto CACHE STRING "The compute device, options are ${DEVICE_LISTING}")
set(HOST Auto CACHE STRING "The compute device, options are ${HOST_LISTING}")
if(NOT ${DEVICE} IN_LIST DEVICE_LISTING)
    message(FATAL_ERROR "You must select a device from ${DEVICE_LISTING}, not ${DEVICE}")
endif()
if(NOT ${HOST} IN_LIST HOST_LISTING)
    message(FATAL_ERROR "You must select a host from ${HOST_LISTING}, not ${HOST}")
endif()

if(DEVICE STREQUAL Auto)
    find_package(CUDA 6.0)
    if(CUDA_FOUND)
        set(DEVICE CUDA CACHE STRING "The compute device, options are ${DEVICE_LISTING}" FORCE)
    else()
        find_package(OpenMP)
        if(OpenMP_CXX_FOUND OR OpenMP_FOUND)
            set(DEVICE OMP CACHE STRING "The compute device, options are ${DEVICE_LISTING}" FORCE)
        else()
            set(DEVICE CPP CACHE STRING "The compute device, options are ${DEVICE_LISTING}" FORCE)
        endif()
    endif()
    message(STATUS "Auto device selection: ${DEVICE}")
endif()

if(HOST STREQUAL Auto)
    if(DEVICE STREQUAL OMP)
        set(HOST OMP CACHE STRING "The host device, options are ${HOST_LISTING}" FORCE)
    elseif(DEVICE STREQUAL TBB)
        set(HOST TBB CACHE STRING "The host device, options are ${HOST_LISTING}" FORCE)
    else()
        set(HOST CPP CACHE STRING "The host device, options are ${HOST_LISTING}" FORCE)
    endif()
    message(STATUS "Auto host selection: ${HOST}")
endif()

set(THRUST_REQUIRED_SYSTEMS ${HOST} ${DEVICE})

FetchContent_Declare(
  thrust
  GIT_REPOSITORY https://github.com/NVIDIA/thrust
  GIT_TAG        1.12.0
  )
FetchContent_MakeAvailable(thrust)
thrust_create_target(MyThrust HOST ${HOST} DEVICE ${DEVICE})
target_compile_features(MyThrust INTERFACE cxx_std_14)

if(DEVICE STREQUAL CUDA)
  enable_language(CUDA)
  set(CMAKE_CUDA_SEPARABLE_COMPILATION ON) # effective when created
else()
  file(GLOB_RECURSE CUDA_FILES *.cu)
  set_source_files_properties(${CUDA_FILES} PROPERTIES LANGUAGE CXX)
  add_compile_options(-x c++)
endif()

add_library(Fit-devicelib INTERFACE)
target_link_libraries(Fit-devicelib INTERFACE MyThrust)


add_library(saxpy STATIC functions.cu)
target_link_libraries(saxpy PUBLIC Fit-devicelib)
add_library(executor STATIC executor.cu)
target_link_libraries(executor PUBLIC saxpy)

add_library(Fit-lib INTERFACE)
target_link_libraries(Fit-lib INTERFACE executor)
target_include_directories(Fit-lib INTERFACE ${PROJECT_SOURCE_DIR})

add_executable(Fit main.cc)
target_link_libraries(Fit PRIVATE Fit-lib)

# test
include(FetchContent)
FetchContent_Declare(
  googletest  
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
set(googletest_BUILD_TESTS OFF)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_subdirectory(tests)
