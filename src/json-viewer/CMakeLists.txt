find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(JSONViewer STATIC
    AppViewer.cpp
    JSONTextEdit.cpp
)

target_include_directories(JSONViewer PUBLIC
    ${CMAKE_SOURCE_DIR})

target_link_libraries(JSONViewer PRIVATE
    Qt5::Core
    Qt5::Widgets
)