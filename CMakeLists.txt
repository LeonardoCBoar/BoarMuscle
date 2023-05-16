cmake_minimum_required(VERSION 3.12)

project(Examples VERSION 1.0.0)

add_executable(Examples
    demo/main.cpp 
    demo/sdl_manager.cpp
)

add_subdirectory(lib)
target_link_libraries(Examples PRIVATE BoarMuscle)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Examples
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

