project(lib)

file(GLOB libFiles *.cpp)

add_subdirectory(js)

set(mainFiles ${mainFiles} ${libFiles} PARENT_SCOPE)
