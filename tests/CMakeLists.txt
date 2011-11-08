project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing

add_executable(test_runner main.cpp)
add_library(loginTest SHARED test_login.cpp)
add_library(userManagerTest SHARED test_usermanager.cpp)
add_dependencies(loginTest wittyPlus)
add_dependencies(userManagerTest wittyPlus)
add_dependencies(test_runner loginTest userManagerTest)

TARGET_LINK_LIBRARIES(loginTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wthttp} wittyPlus)
TARGET_LINK_LIBRARIES(userManagerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wtdbo} ${wthttp} wittyPlus)

TARGET_LINK_LIBRARIES(test_runner loginTest userManagerTest)

set(TEST_EXE_NAME tests/test_runner PARENT_SCOPE)

CONFIGURE_FILE(memcheck-test.sh memcheck-test.sh)
CONFIGURE_FILE(test.sh test.sh)

