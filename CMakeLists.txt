cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(particle-sim)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(fmt REQUIRED)

set(SOURCE_FILES src/main.cpp
    src/particle.cpp src/vectors.cpp
)


file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} 
    PRIVATE SDL2::SDL2-static 
    PRIVATE ${SDL2TTF_LIBRARY}
    PRIVATE fmt
)
