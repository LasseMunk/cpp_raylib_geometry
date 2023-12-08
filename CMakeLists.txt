cmake_minimum_required(VERSION 3.27.7)
set(CMAKE_CXX_STANDARD 20)
project(lm_raylib_geometry VERSION 0.0.1)

#Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.0)
FetchContent_Declare( # Check if the version of raylib is installed on the machine, if not then download and make available
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
# We don't want to build the examples - we only need the library
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# set(RAYGUI_VERSION 4.0)
# FetchContent_Declare(
#     raygui
#     URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.zip
#     FIND_PACKAGE_ARGS ${RAYGUI_VERSION}
# )

# FetchContent_MakeAvailable(raygui)

# Our project
# set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME})

# `target_sources` adds source files to a target. We pass the target that needs the sources as the
# first argument, then a visibility parameter for the sources which should normally be PRIVATE.
# Finally, we supply a list of source files that will be built into the target. This is a standard
# CMake command.
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        ${INCLUDE_DIR}/raygui.h
        
)

# Sets the include directories of the plugin project.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${INCLUDE_DIR}
)


target_link_libraries(${PROJECT_NAME}  raylib) # Link the raylib library to our project


# Checks if OSX and links appropriate frameworks
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()