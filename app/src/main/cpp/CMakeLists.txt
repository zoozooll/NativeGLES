cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -funwind-tables")

project("nativeGL")

include_directories(".")

file(GLOB nativeGL_SRC
        "./*.cpp"
        )

add_library(${CMAKE_PROJECT_NAME} SHARED ${nativeGL_SRC})

find_library(log-lib log)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        GLESv3
        android
        EGL
        atomic
        jnigraphics
        ${log-lib})