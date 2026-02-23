

set(PROJECT_NAME "test")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    src/main.cpp
)