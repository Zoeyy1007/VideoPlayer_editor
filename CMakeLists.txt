cmake_minimum_required(VERSION 3.10)
project(VideoPlayer)

set(CMAKE_CXX_STANDARD 11)

# For Qt6
set(Qt6_DIR "/opt/homebrew/opt/qt/lib/cmake/Qt6")

find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(VideoPlayer main.cpp)

target_include_directories(VideoPlayer PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(VideoPlayer ${OpenCV_LIBS})
target_link_libraries(VideoPlayer Qt6::Core Qt6::Widgets Qt6::Gui)