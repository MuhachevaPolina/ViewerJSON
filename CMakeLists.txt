cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(json-viewer VERSION 1.0.0 DESCRIPTION "Графический просмотрщик JSON")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(src/json-viewer)

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

find_package(GTest REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(app
    src/main.cpp
)

target_link_libraries(app PRIVATE
    JSONViewer
    Qt5::Core
    Qt5::Widgets
)


# enable_testing()
# add_subdirectory(test)
