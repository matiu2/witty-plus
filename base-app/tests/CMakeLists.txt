project(tests)

ADD_DEFINITIONS( -fno-access-control )

add_executable(test_runner main.cpp)

add_library(tests SHARED test_login.cpp)

TARGET_LINK_LIBRARIES(tests mainApp)

TARGET_LINK_LIBRARIES(test_runner tests)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

