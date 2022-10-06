cmake_minimum_required(VERSION 3.15)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

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
    add_definitions("-std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0")
endif(CMAKE_COMPILER_IS_GNUCXX)

#if(MSVC)
#    add_compile_options(std:c++17)
#endif()

include_directories(
  ${CONAN_INCLUDE_DIRECTORIES}
)

#####    CLIENT

FILE(GLOB_RECURSE ENGINE src/Engine/*.cpp)
FILE(GLOB_RECURSE ENGINE_HPP src/Engine/*.hpp)
FILE(GLOB_RECURSE SYSTEMS src/Systems/*.cpp)
FILE(GLOB_RECURSE SRCS_CLIENT src/Client/*.cpp src/Client/*.hpp)

###### toolsclient.so

# add_library(Engine SHARED ${ENGINE} ${ENGINE_HPP})




##### client-Rtype

add_executable(Client-Rtype ${ENGINE} ${SYSTEMS} ${SRCS_CLIENT})

target_include_directories(
  Client-Rtype PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_libraries(
  Client-Rtype
  PRIVATE
  ${CONAN_LIBS}
)

#####    SERVER

FILE(GLOB_RECURSE SRCS_SERVER src/Server/*.cpp)
FILE(GLOB_RECURSE SYSTEMSSRV src/SystemsServer/*.cpp)

add_executable(Server-Rtype ${SRCS_SERVER} ${ENGINE} ${SYSTEMSSRV})

target_include_directories(
  Server-Rtype PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_libraries(
  Server-Rtype
  PRIVATE
  ${CONAN_LIBS}
)
