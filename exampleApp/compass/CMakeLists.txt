project(compass)

# Copy to a working compass dir
FILE(COPY src stylesheets DESTINATION .)

# Set the output type
if (DEBUG)
    set(COMPASS_OUTPUT_STYLE ":extended")
else()
    set(COMPASS_OUTPUT_STYLE ":compressed")
endif()

set(COMPASS_OUTPUT_DIR "../static-content/resources/themes/default")

# Copy it to the temp dir
configure_file(config.rb.in config.rb)

add_custom_target(css 
    COMMAND compass compile .
    WORKING_DIRECTORY .
    DEPENDS config.rb
    COMMENT "Running Compass to generate style sheets"
)
