cmake_minimum_required(VERSION 3.16)


if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


set(PROJECT_NAME "test")

project(${PROJECT_NAME}
  VERSION 1.0
    LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${PROJECT_NAME}
  PRIVATE
    src/main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:-O3 -ffast-math>
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra )
endif()
