cmake_minimum_required(VERSION 3.14)

project(RESTserver LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)

add_executable(RESTserver
  main.cpp
  rest_server.h
  rest_server.cpp

  parser.h
  parser.cpp

  database.h
  database.cpp

  databaselog.h
  databaselog.cpp

  Command.h
  Mode.h
)
target_link_libraries(RESTserver Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(RESTserver Qt${QT_VERSION_MAJOR}::Network)
