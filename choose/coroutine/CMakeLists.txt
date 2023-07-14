cmake_minimum_required(VERSION 3.14)

project(Concurrency)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the include paths
include_directories("./header")

set(HEADER_FILES "./header")
set(SOURCE_FILES "./src")

file(GLOB SOURCE_LIST "${SOURCE_FILES}/*.cpp")
file(GLOB HEADER_LIST "${HEADER_FILES}/*.h")

add_executable(${PROJECT_NAME} ${HEADER_LIST} ${SOURCE_LIST})
