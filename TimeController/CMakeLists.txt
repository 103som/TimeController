cmake_minimum_required(VERSION 3.14)

project(TimeController LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Network Sql REQUIRED)

add_executable(TimeController
  main.cpp
  server.h
  server.cpp
  clientDB.h
  clientDB.cpp
)
target_link_libraries(TimeController Qt6::Core Qt6::Network Qt6::Sql)

install(TARGETS TimeController
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
