CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(my_app)

ADD_DEFINITIONS(-Wall -Wextra)

# Settings for configuration and script files
IF( "${CMAKE_BUILD_TYPE}" STREQUAL Release )
  SET(DEBUG false)
ELSE()
  SET(DEBUG true)
ENDIF()
SET(LOG_FILE_NAME "${PROJECT_NAME}.log")
SET(EXE_NAME ${PROJECT_NAME})
option(WTDebug "Use the witty debug libraries ? (wtd.so etc.)" off)
# Options that we're gonna add
option(DBO "Use witty DBO" on)
#set(DB_CONNECTION_STRING host=localhost user=my_app dbname=my_app password=my_app cache string "http://www.postgresql.org/docs/8.1/static/libpq.html")
set( DB_CONNECTION_STRING "host=localhost user=my_app dbname=my_app password=my_app" CACHE string "DB Connection string")
message("DB Connection string is: ${DB_CONNECTION_STRING}")
option(UserSessions "Use long term user logon sessions, (requires dbo)" on)

# Configuration and script files
CONFIGURE_FILE(wt-config.xml wt-config.xml)
CONFIGURE_FILE(gdb-run.sh gdb-run.sh)
CONFIGURE_FILE(memcheck-run.sh memcheck-run.sh)
CONFIGURE_FILE(run.sh run.sh)
CONFIGURE_FILE(deployrun.sh deployrun.sh)

# Copy static files and directories
FILE(COPY messages static-content DESTINATION .)

# Sort out our libraries
#if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
if (WTDebug)
    find_library(wt wtd)
    find_library(wthttp wthttpd)
    find_library(wtdbo wtdbod)
    find_library(wtdbopostgres wtdbopostgresd)
else()
    find_library(wt wt)
    find_library(wthttp wthttp)
    find_library(wtdbo wtdbo)
    find_library(wtdbopostgres wtdbopostgres)
endif()

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)

find_package(OpenSSL 1.0.0 REQUIRED)
include_directories(BEFORE ${OPENSSL_INCLUDE_DIR})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.42.0 REQUIRED COMPONENTS system program_options signals date_time filesystem regex thread unit_test_framework)
include_directories(BEFORE SYSTEM ${Boost_INCLUDE_DIR})

set(mainFiles urls.cpp UserEdit.cpp lib/MemorySessionStore.cpp  lib/BaseSessionHandle.cpp App.cpp MainWindow.cpp LoginWindow.cpp UserList.cpp)

add_subdirectory(lib)
add_subdirectory(tests)
CONFIGURE_FILE(memcheck-test.sh memcheck-test.sh)

# Build the library
ADD_LIBRARY(mainLib SHARED ${mainFiles})

# Build the executable
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)

TARGET_LINK_LIBRARIES(mainLib
    ${Boost_THREAD_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY}
    ${OPENSSL_LIBRARIES} ${wt} ${wtdbo} ${wtdbopostgres} ${wthttp} 
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} mainLib)
add_dependencies(${PROJECT_NAME} mainLib)

# Just to get started, this program will set up the DB with some basic users
ADD_EXECUTABLE(setupDB setupDB.cpp)
TARGET_LINK_LIBRARIES(setupDB ${Boost_SYSTEM_LIBRARY} ${OPENSSL_LIBRARIES} ${wt} ${wtdbo} ${wtdbopostgres})
set_target_properties(setupDB PROPERTIES COMPILE_DEFINITIONS CMAKE_DB_CONNECTION_STRING="${DB_CONNECTION_STRING}" )
