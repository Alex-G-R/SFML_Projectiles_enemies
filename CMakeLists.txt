cmake_minimum_required(VERSION 3.24)
project(SFML_Balls)

set(CMAKE_CXX_STANDARD 14)

add_executable(SFML_Balls main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/dev/DEVEL/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/dev/DEVEL/SFML/include/SFML)
target_link_libraries(SFML_Balls sfml-system sfml-window sfml-graphics sfml-audio)