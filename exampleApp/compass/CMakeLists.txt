project(compass)

# Put them where the app can read them
get_filename_component(COMPILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
# Hacky thing to turn our absolute path into a relative path .. need to pretend we have a file there already
file(RELATIVE_PATH PRINT_CSS_PATH "${COMPILE_DIR}" "${CSS_OUTPUT_DIR}/print.css")
get_filename_component(CSS_OUTPUT_DIR "${PRINT_CSS_PATH}" PATH)

# Set the output format
if (${DEBUG})
    set(COMPASS_OUTPUT_STYLE ":extended") # Long hand for debugging
else()
    set(COMPASS_OUTPUT_STYLE ":compressed") # Compressesd for release
endif()

# Copy it to the temp dir
configure_file(config.rb.in "${COMPILE_DIR}/config.rb")

add_custom_target(css ALL
    COMMAND compass compile .
    WORKING_DIRECTORY ${COMPILE_DIR}
    DEPENDS "${COMPILE_DIR}/config.rb"
    COMMENT "Running Compass to generate style sheets"
)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES .sass-cache)
