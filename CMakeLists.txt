cmake_minimum_required(VERSION 3.15)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

Project (R-TYPE)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup()

find_package(SFML 2.5.1 COMPONENTS window graphics system network audio REQUIRED)
find_package(asio REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

#todo: trouver un autre moyen parce que on compile pas sous linux avec le flag abi=0
if(CMAKE_COMPILER_IS_GNUCXX) # Pour régler le problème du sf:string:string undefined
    #add_definitions("-std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0")
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

FILE(GLOB_RECURSE SRCS_NETWORK src/Network/*.cpp)
FILE(GLOB_RECURSE SRCS_SERVER src/Server/*.cpp)
FILE(GLOB_RECURSE SRCS_CLIENT src/Client/*.cpp)
FILE(GLOB_RECURSE SRCS_SCENE src/Scene/*.cpp)

#####   CLIENT

add_executable(Client-Rtype ${SRCS_CLIENT} ${SRCS_SCENE} ${SRCS_NETWORK})

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
  PRIVATE
  ${CONAN_LIBS}
  EngineCoreSuper
)

# target_link_libraries(
#   Client-Rtype
#   PUBLIC
#   EngineCoreSuper
# )

#####    SERVER

add_executable(Server-Rtype ${SRCS_SERVER} ${SRCS_NETWORK})

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
  ${CONAN_LIBS}
  EngineCoreSuper
)

# target_link_libraries(
#   Server-Rtype
#   PUBLIC
  
# )