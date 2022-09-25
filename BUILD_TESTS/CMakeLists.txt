cmake_minimum_required(VERSION 3.15)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)



Project (Rutabaga)
add_subdirectory(dependencies)
FILE(GLOB_RECURSE SRCS src/Game/*.cpp)

add_executable(Rutabaga ${SRCS})

target_link_libraries(Rutabaga
    PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
)

if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET Rutabaga POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:Rutabaga>)
  endif()
endif()