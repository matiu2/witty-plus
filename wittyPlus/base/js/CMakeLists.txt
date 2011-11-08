project(js)

file(GLOB jsFiles *.cpp)

set(mainFiles ${mainFiles} ${jsFiles} PARENT_SCOPE)
