project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing

set(TEST_EXE_NAME test_runner)

CONFIGURE_FILE(wt-config.xml wt-config.xml)
add_executable(test_runner main.cpp)

add_library(loginTest SHARED test_login.cpp)
TARGET_LINK_LIBRARIES(loginTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wthttp} wittyPlus)

add_library(userManagerTest SHARED test_usermanager.cpp)
TARGET_LINK_LIBRARIES(userManagerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wtdbo} ${wthttp} wittyPlus)

add_library(urlTest SHARED test_urlMatcher.cpp)
TARGET_LINK_LIBRARIES(urlTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wtdbo} ${wthttp} wittyPlus)

TARGET_LINK_LIBRARIES(test_runner loginTest userManagerTest urlTest)

CONFIGURE_FILE(memcheck-test.sh memcheck-test.sh)
CONFIGURE_FILE(test.sh test.sh)

