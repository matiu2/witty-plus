CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(wittyPlus)

set(mainFiles url2action.cpp IGui.cpp IUsers.cpp INavigation.cpp urls.cpp UserEdit.cpp lib/MemorySessionStore.cpp  lib/BaseSessionHandle.cpp App.cpp db.cpp MainWindow.cpp LoginWindow.cpp UserList.cpp)

add_subdirectory(lib)

# Build the library
ADD_LIBRARY(${PROJECT_NAME} SHARED ${mainFiles})

add_subdirectory(extensions)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${Boost_THREAD_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY}
    ${OPENSSL_LIBRARIES} ${wt} ${wtdbo} ${wtdbopostgres} ${wthttp} 
    extensions
)

