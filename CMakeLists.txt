cmake_minimum_required(VERSION 2.6)

project(test-app)

file(GLOB HEADERS header/*.h)
file(GLOB SOURCES source/*.cpp)

include_directories( ./header )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(test-app tinyxml)
