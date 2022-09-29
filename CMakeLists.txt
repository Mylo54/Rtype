cmake_minimum_required(VERSION 3.15)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

Project (R-TYPE)
include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup()

find_package(SFML 2.5.1 COMPONENTS window graphics system network audio REQUIRED)
find_package(asio REQUIRED)
find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX) # Pour régler le problème du sf:string:string undefined
    message(STATUS "GNUCXX detected, proceed ")
    add_definitions("-std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(
  ${CONAN_INCLUDE_DIRECTORIES}
)

#####    CLIENT

FILE(GLOB_RECURSE SRCS_CLIENT src/Game/Client/*.cpp)

add_executable(Client-Rutabaga ${SRCS_CLIENT})

target_include_directories(
  Client-Rutabaga PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_libraries(
  Client-Rutabaga
  PRIVATE
  ${CONAN_LIBS}
  sfml-graphics
  sfml-system
  sfml-window
  sfml-audio
  sfml-network
)

#####    SERVER

FILE(GLOB_RECURSE SRCS_SERVER src/Game/Server/*.cpp)

add_executable(Server-Rutabaga ${SRCS_SERVER})

target_include_directories(
  Server-Rutabaga PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_libraries(
  Server-Rutabaga
  PRIVATE
  ${CONAN_LIBS}
  sfml-graphics
  sfml-system
  sfml-window
  sfml-audio
  sfml-network
)

#####    ENGINE (temporary)

FILE(GLOB_RECURSE SRCS_ENGINE src/Engine/*.cpp)

add_executable(Engine-Rutabaga ${SRCS_ENGINE})

target_include_directories(
  Engine-Rutabaga PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_libraries(
  Engine-Rutabaga
  PRIVATE
  ${CONAN_LIBS}
  sfml-graphics
  sfml-system
  sfml-window
  sfml-audio
  sfml-network
)