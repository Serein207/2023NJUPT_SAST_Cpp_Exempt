cmake_minimum_required(VERSION 3.10)
project(crtp_probleam VERSION 1.0 LANGUAGES CXX)
add_executable(crtp_probleam src/main.cpp src/vec_2d.cpp src/vec_3d.cpp)
set_target_properties(crtp_probleam PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)
target_include_directories(crtp_probleam PUBLIC include)