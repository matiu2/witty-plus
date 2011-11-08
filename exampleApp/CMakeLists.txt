project(exampleApp)

# Configuration and script files
CONFIGURE_FILE(wt-config.xml wt-config.xml)
CONFIGURE_FILE(gdb-run.sh gdb-run.sh)
CONFIGURE_FILE(memcheck-run.sh memcheck-run.sh)
CONFIGURE_FILE(run.sh run.sh)
CONFIGURE_FILE(deployrun.sh deployrun.sh)

add_subdirectory(compass)

# Copy static files and directories
FILE(COPY messages static-content DESTINATION .)

# Build the executable
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} wittyPlus)
add_dependencies(${PROJECT_NAME} wittyPlus)
