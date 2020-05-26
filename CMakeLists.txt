cmake_minimum_required(VERSION 3.8)
project(ff7tk VERSION 0.80.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(WIDGET_GALLERY "Build the widget based gallery" OFF)
option(QML_GALLERY "Build the qml based gallery" OFF)
option(DOCS "Build and Install Documents (Requires Doxygen)" OFF)

if(WIDGET_GALLERY)
    add_subdirectory(ff7tkWidgetGallery)
endif()

if(QML_GALLERY)
    add_subdirectory(ff7tkQmlGallery)
endif()

if (DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(src)
