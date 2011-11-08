CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(wittyPlusBase)

ADD_DEFINITIONS(-std=c++0x -Wall -Wextra)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}) # So we can go '#include <wittyPlus>

add_subdirectory(wittyPlus)
