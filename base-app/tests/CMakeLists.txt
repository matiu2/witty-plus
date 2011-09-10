project(tests)

ADD_DEFINITIONS( -fno-access-control )

add_executable(test_runner main.cpp)
add_library(tests SHARED test_login.cpp)
add_dependencies(tests mainLib)
add_dependencies(test_runner tests)

TARGET_LINK_LIBRARIES(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wthttp} mainLib)

TARGET_LINK_LIBRARIES(test_runner tests)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

