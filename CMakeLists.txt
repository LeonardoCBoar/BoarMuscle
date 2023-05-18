cmake_minimum_required(VERSION 3.12)

project(Examples VERSION 1.0.0)

add_executable(Examples
    demo/main.cpp 
    demo/graphical_manager.cpp
)

add_subdirectory(lib)
target_link_libraries(Examples PRIVATE BoarMuscle)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Examples PRIVATE ${SDL2_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(Examples PRIVATE ${OPENGL_LIBRARIES})
