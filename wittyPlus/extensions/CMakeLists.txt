PROJECT(extensions)

set(dependencies 
    ${Boost_THREAD_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${wt} ${wtdbo} ${wtdbopostgres})

# Page plugin
option(extPage "Build and use the Page extension? Provides a databased hierachy of standard pages with CRUD" on)
if (extPage)
    add_subdirectory(page)
    ADD_DEFINITIONS(-DEXT_PAGE)
    set(dependencies ${dependencies} page)
endif()

add_library(${PROJECT_NAME} SHARED ExtensionManager.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${dependencies})
