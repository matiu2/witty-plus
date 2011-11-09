PROJECT(wittyPlusExtensions)

# Page plugin
option(extPage "Build and use the Page extension? Provides a databased hierachy of standard pages with CRUD" on)
if (extPage)
    add_subdirectory(page)
    ADD_DEFINITIONS(-DEXT_PAGE)
endif()
