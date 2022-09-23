cmake_minimum_required(VERSION 3.15)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

#### UDEV INSTALL TEST ####

FIND_PATH(
    UDEV_INCLUDE_DIR
    libudev.h
    /usr/include
    /usr/local/include
    ${UDEV_PATH_INCLUDES}
)

FIND_LIBRARY(
    UDEV_LIBRARIES
    NAMES udev libudev
    PATHS
        /usr/lib${LIB_SUFFIX}
        /usr/local/lib${LIB_SUFFIX}
        ${UDEV_PATH_LIB}
)

IF (UDEV_LIBRARIES AND UDEV_INCLUDE_DIR)
    SET(UDEV_FOUND "YES")
    execute_process(COMMAND pkg-config --atleast-version=143 libudev RESULT_VARIABLE UDEV_STABLE)
    # retvale is 0 of the condition is "true" so we need to negate the value...
    if (UDEV_STABLE)
set(UDEV_STABLE 0)
    else (UDEV_STABLE)
set(UDEV_STABLE 1)
    endif (UDEV_STABLE)
    message(STATUS "libudev stable: ${UDEV_STABLE}")
ENDIF (UDEV_LIBRARIES AND UDEV_INCLUDE_DIR)

IF (UDEV_FOUND)
    MESSAGE(STATUS "Found UDev: ${UDEV_LIBRARIES}")
    MESSAGE(STATUS " include: ${UDEV_INCLUDE_DIR}")
ELSE (UDEV_FOUND)
    MESSAGE(STATUS "UDev not found.")
    MESSAGE(STATUS "UDev: You can specify includes: -DUDEV_PATH_INCLUDES=/opt/udev/include")
    MESSAGE(STATUS " currently found includes: ${UDEV_INCLUDE_DIR}")
    MESSAGE(STATUS "UDev: You can specify libs: -DUDEV_PATH_LIB=/opt/udev/lib")
    MESSAGE(STATUS " currently found libs: ${UDEV_LIBRARIES}")
    IF (UDev_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find UDev library")
    ENDIF (UDev_FIND_REQUIRED)
ENDIF (UDEV_FOUND)


##########################

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

#TEST