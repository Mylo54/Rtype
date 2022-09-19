cmake_minimum_required(VERSION 3.11)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)


set(SFML_VERSION "2.5.1")

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

Project (Rutabaga)

FILE(GLOB_RECURSE SRCS src/Client/*.cpp)

add_executable(Rutabaga ${SRCS})

target_link_libraries(Rutabaga
    PRIVATE
    sfml-audio
    sfml-graphics
    sfml-system
    sfml-window
)