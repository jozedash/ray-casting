cmake_minimum_required(VERSION 3.0)
project(raycast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(PLATFORM_OUTPUT_DIR "Windows")
else()
    set(PLATFORM_OUTPUT_DIR "Linux")
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PLATFORM_OUTPUT_DIR}/bin"
)