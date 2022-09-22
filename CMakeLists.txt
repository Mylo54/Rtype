cmake_minimum_required(VERSION 3.11)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)



Project (Rutabaga)
add_subdirectory(dependencies)
FILE(GLOB_RECURSE SRCS src/Game/Client/*.cpp)

add_executable(Rutabaga ${SRCS})

target_link_libraries(Rutabaga
    PRIVATE
    sfml-audio
    sfml-graphics
    sfml-system
    sfml-window
)