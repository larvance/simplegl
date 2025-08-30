cmake_minimum_required(VERSION 4.0)
project(opengltest)

set(CMAKE_CXX_STANDARD 23)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(src)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.hpp
)

add_executable(opengltest ${SOURCES})

target_compile_definitions(opengltest PRIVATE GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(opengltest
        PRIVATE glfw
        PRIVATE glm::glm
        PRIVATE OpenGL::GL
        PRIVATE glad::glad
)

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O1 /DNDEBUG /EHsc /GR- /bigobj")
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1 -g0 -fno-rtti -fno-exceptions")
endif ()
