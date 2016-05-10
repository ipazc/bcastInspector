cmake_minimum_required(VERSION 3.3)
project(bcastInspector)

set(gcc "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/networkdisplay.c src/networking.c src/filters/stormbcastfilter.c src/list/macList.c main.c)

add_executable(bcastInspector ${SOURCE_FILES})

target_link_libraries(bcastInspector pcap)
