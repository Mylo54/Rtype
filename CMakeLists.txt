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
find_package(Boost REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX) # Pour régler le problème du sf:string:string undefined
    add_definitions("-std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0")
endif(CMAKE_COMPILER_IS_GNUCXX)

#if(MSVC)
#    add_compile_options(std:c++17)
#endif()

if (APPLE)
	add_definitions(-DAPPLE)
elseif (WIN32)
	add_definitions(-DWINDOWS)
	add_definitions(-D_WIN32_WINNT=0x0A00)
endif (APPLE)


include_directories(
  external/EngineCoreSuper/include
  ${CONAN_INCLUDE_DIRECTORIES}
)

add_subdirectory(external/EngineCoreSuper)

#####   Files

FILE(GLOB_RECURSE CLIENT_SYSTEMS src/ClientSystems/*.cpp)
FILE(GLOB_RECURSE SERVER_SYSTEMS src/ServerSystems/*.cpp)
FILE(GLOB_RECURSE SRCS_SERVER src/Server/*.cpp)
FILE(GLOB_RECURSE SRCS_CLIENT src/Client/*.cpp)

#####   CLIENT

add_executable(Client-Rtype ${CLIENT_SYSTEMS} ${SRCS_CLIENT})

target_include_directories(
  Client-Rtype PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_directories(
  Client-Rtype
  PRIVATE
  external/EngineCoreSuper/build
)

target_link_libraries(
  Client-Rtype
  EngineCoreSuper
  ${CONAN_LIBS}
)

#####    SERVER

add_executable(Server-Rtype ${SERVER_SYSTEMS} ${SRCS_SERVER})

target_include_directories(
  Server-Rtype PUBLIC
  ${CONAN_INCLUDE_DIRECTORIES}
)

target_link_directories(
  Server-Rtype PUBLIC
  external/EngineCoreSuper/build
)

target_link_libraries(
  Server-Rtype
  EngineCoreSuper
  ${CONAN_LIBS}
)
