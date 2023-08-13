cmake_minimum_required(VERSION 3.0.0)

project(ex3 VERSION 0.1.0)

set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors -L.")

set(MTM_FLAGS_RELEASE "{MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_library(date partA/date.c partA/date.h)

add_executable(ex3  provided/test_partC.cpp partB/student.cpp partA/date_wrap.cpp partB/base_event.cpp partB/closed_event.cpp partB/event_container.cpp partB/festival.cpp partB/open_event.cpp partC/schedule.cpp)

target_link_libraries(ex3 -ldate)
