project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing
ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So tests load the test lib dynamically

# A Function for integrating BOOST.TEST and CTEST a little bit
# if MAIN_NAME is number:
#   source file will be: test_number.cpp
#   executable file will be: test_number
# Any other args are the tests to run on it
function(boost_test MAIN_NAME)
    set(EXE_NAME test_${MAIN_NAME})
    ADD_EXECUTABLE(${EXE_NAME} test_${MAIN_NAME}.cpp)
    TARGET_LINK_LIBRARIES(${EXE_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wt} ${wtdbo} ${wthttp} ${wttest} wittyPlus)
    FOREACH(TEST IN ITEMS ${ARGN})
        ADD_TEST(
            ${TEST}
            ${EXE_NAME} -i -s --detect_fp_exceptions=y --log-level=all --run_test=${MAIN_NAME}_suite/${TEST})
        if (${RunMemoryChecks})
            ADD_TEST(
                ${TEST}_valgrind
                valgrind --leak-check=yes --log-file=valgrind_${TEST}.out.txt ./${EXE_NAME} -i -s
                         --detect_fp_exceptions=y --log-level=all DEBUG --run_test=${MAIN_NAME}_suite/${TEST})
        endif()
    endforeach()
endfunction()

CONFIGURE_FILE(wt-config.xml wt-config.xml)

boost_test(
    login
    login_escape
    login_enter
    login_ok
    login_cancel
    login_fail
    login_logout
)

boost_test(
    usermanager
    new_user
    new_forget_password
)

boost_test(
    urlMatcher
    find_handlers
)
