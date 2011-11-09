PROJECT(page)

ADD_LIBRARY(page SHARED Page.cpp Extension.cpp)
TARGET_LINK_LIBRARIES(page wittyPlus)
