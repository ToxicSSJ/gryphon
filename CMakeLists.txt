cmake_minimum_required(VERSION 3.14)
project(gryphon)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "--coverage")

add_executable(gryphon gryphon.cpp)

add_subdirectory(deps/spdlog)
add_subdirectory(deps/simpleson)
add_subdirectory(deps/sleepy-discord)
add_subdirectory(deps/yaml-cpp)

target_link_libraries(gryphon ${PYTHON_LIBRARIES})
target_link_libraries(gryphon -static)
target_link_libraries(gryphon sleepy-discord)
target_link_libraries(gryphon simpleson)
target_link_libraries(gryphon spdlog)
target_link_libraries(gryphon yaml-cpp)