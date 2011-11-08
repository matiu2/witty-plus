project(utils)

# Just to get started, this program will set up the DB with some basic users
ADD_EXECUTABLE(setupDB setupDB.cpp)
TARGET_LINK_LIBRARIES(setupDB ${Boost_SYSTEM_LIBRARY} ${OPENSSL_LIBRARIES} ${wt} ${wtdbo} ${wtdbopostgres})
set_target_properties(setupDB PROPERTIES COMPILE_DEFINITIONS CMAKE_DB_CONNECTION_STRING="${DB_CONNECTION_STRING}" )

