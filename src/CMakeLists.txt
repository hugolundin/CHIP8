set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Create a main executable for the project.
add_executable(
    main
    main.c
    cpu.c
)

target_link_libraries(
    main
    PUBLIC
    ${SDL2_LIBRARY}
)

target_include_directories(
    main
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL_INCLUDE_DIR}
)
