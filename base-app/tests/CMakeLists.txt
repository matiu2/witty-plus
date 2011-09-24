project(tests)

ADD_DEFINITIONS( -fno-access-control )

add_executable(test_runner main.cpp)
add_library(loginTest SHARED test_login.cpp)
add_library(userManagerTest SHARED test_usermanager.cpp)
add_dependencies(loginTest mainLib)
add_dependencies(userManagerTest mainLib)
add_dependencies(test_runner loginTest userManagerTest)

TARGET_LINK_LIBRARIES(loginTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wthttp} mainLib)
TARGET_LINK_LIBRARIES(userManagerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wtdbo} ${wthttp} mainLib)

TARGET_LINK_LIBRARIES(test_runner loginTest userManagerTest)

set(TEST_EXE_NAME tests/test_runner PARENT_SCOPE)

