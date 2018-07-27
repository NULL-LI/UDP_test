cmake_minimum_required(VERSION 2.8.3)
project(UDP_test)

#set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )
add_compile_options(-std=c++11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-march=native -O0 -Wall  -pthread")
set(QMAKE_CXXFLAGS += -g)

include_directories( ${PROJECT_SOURCE_DIR} )

add_executable(udp_server udp_server.cpp)
add_executable(udp_client udp_client.cpp)
# target_link_libraries(rrt-test Qt5::Widgets Qt5::Gui)
