cmake_minimum_required(VERSION 3.15)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


Project (Rutabaga)
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

# add_subdirectory(dependencies)
FILE(GLOB_RECURSE SRCS src/Game/*.cpp)

add_executable(Rutabaga ${SRCS})

include_directories(
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_include_directories(
  Rutabaga PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)



#link_libraries(
#  ${CONAN_LIBS}
#)

target_link_libraries(
  Rutabaga
  PRIVATE
  ${CONAN_LIBS}
  sfml-graphics
  sfml-system
  sfml-window
  sfml-audio
  sfml-network
)