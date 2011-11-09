PROJECT(wittyPlusPageExtension)

ADD_LIBRARY(wittyPlusPageExtension SHARED Extension.cpp Model.cpp)
TARGET_LINK_LIBRARIES(wittyPlusPageExtension wittyPlus)
