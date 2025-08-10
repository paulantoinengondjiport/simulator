cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SFML as static libraries" FORCE)

project(simulator)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/SFML")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(simulator ${MY_SOURCES})
set_target_properties(simulator PROPERTIES
        OUTPUT_NAME "simulator")

#set_target_properties(simulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" OUTPUT_NAME "simulator.bin") //Build in bin not compatible with IDE
target_include_directories(simulator PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(simulator PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
)