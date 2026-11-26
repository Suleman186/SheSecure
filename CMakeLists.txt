cmake_minimum_required(VERSION 3.16)
project(SheSecure VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_add_executable(SheSecure
src/main.cpp
src/mainwindow.h
src/mainwindow.cpp
src/contactstore.h
src/contactstore.cpp
)
target_link_libraries(SheSecure PRIVATE Qt6::Widgets)
