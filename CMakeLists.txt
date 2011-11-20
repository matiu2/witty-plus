CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT(wittyPlusBase)

ADD_DEFINITIONS(-std=c++0x -Wall -Wextra)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}) # So we can go '#include <wittyPlus>

# Settings for configuration and script files
IF( "${CMAKE_BUILD_TYPE}" STREQUAL Release )
  SET(DEBUG false)
ELSE()
  SET(DEBUG true)
  ADD_DEFINITIONS(-DBOOST_DISABLE_ASSERTS)
ENDIF()
SET(LOG_FILE_NAME "${PROJECT_NAME}.log")
option(WTDebug "Use the witty debug libraries ? (wtd.so etc.)" off)
# Options that we're gonna add
option(DBO "Use witty DBO" on)
#set(DB_CONNECTION_STRING host=localhost user=wittyPlus dbname=wittyPlus password=wittyPlus cache string "http://www.postgresql.org/docs/8.1/static/libpq.html")
set( DB_CONNECTION_STRING "host=localhost user=witty_plus dbname=witty_plus password=witty_plus" CACHE string "DB Connection string")
message("DB Connection string is: ${DB_CONNECTION_STRING}")

# More options
set(UserSessions on CACHE BOOL "Use long term user logon sessions, (requires dbo)")

set(RunTests on CACHE BOOL "Run the testing code")
set(RunMemoryChecks on CACHE BOOL "Run the testing code with valgrind memory leak detection")

if (${RunTests}) 
    enable_testing()
endif()

# Sort out our libraries
#if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
if (WTDebug)
    find_library(wt wtd)
    find_library(wthttp wthttpd)
    find_library(wtdbo wtdbod)
    find_library(wtdbopostgres wtdbopostgresd)
    find_library(wttest wttestd)
else()
    find_library(wt wt)
    find_library(wthttp wthttp)
    find_library(wtdbo wtdbo)
    find_library(wtdbopostgres wtdbopostgres)
    find_library(wttest wttest)
endif()

find_package(OpenSSL REQUIRED)
include_directories(BEFORE ${OPENSSL_INCLUDE_DIR})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.42.0 REQUIRED COMPONENTS system program_options signals date_time filesystem regex thread unit_test_framework)
include_directories(BEFORE SYSTEM ${Boost_INCLUDE_DIR})

# Sub directories
add_subdirectory(wittyPlus)
add_subdirectory(utils)
add_subdirectory(tests)
add_subdirectory(exampleApp)
