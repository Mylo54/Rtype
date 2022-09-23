include(FetchContent)

set(SFML_VERSION "2.5.1")

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG "${SFML_VERSION}" # 2.5.1
)

add_subdirectory(sfml)


#FetchContent_Declare(
#  sfml
#  GIT_REPOSITORY "https://github.com/SFML/SFML"
#  GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # 2.5.1
#)