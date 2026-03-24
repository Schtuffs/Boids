cmake_minimum_required(VERSION 3.25)

project(boids LANGUAGES C CXX)

find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(WINDOW_INC ${CMAKE_CURRENT_LIST_DIR}/include/window)
set(WINDOW_SRC ${CMAKE_CURRENT_LIST_DIR}/src/window)
set(SRC src)
set(INCLUDE include)

add_executable(${PROJECT_NAME}
    ${WINDOW_SRC}/glad.c
    ${WINDOW_SRC}/Colour.cpp
    ${WINDOW_SRC}/Library.cpp
    ${WINDOW_SRC}/Renderable.cpp
    ${WINDOW_SRC}/RenderManager.cpp
    ${WINDOW_SRC}/Window.cpp
    ${WINDOW_SRC}/WindowManager.cpp
    ${SRC}/Boid.cpp
    ${SRC}/Callbacks.cpp
    ${SRC}/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${WINDOW_INC} ${INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw stdc++exp)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
        ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
    set_source_files_properties(${WINDOW_SRC}/glad.c PROPERTIES COMPILE_OPTIONS -Wno-pedantic)
endif()

