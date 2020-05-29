cmake_minimum_required(VERSION 3.8)


# Project


project("lizy1.kurisu" VERSION 0)
set(NAME_PACKAGE               "${PROJECT_NAME}")
set(NAME_PACKAGE_WITH_VERSION  "${PROJECT_NAME}-${PROJECT_VERSION}")
set(NAME_LIB_MAIN              "${PROJECT_NAME}")


# Project - Directory


set(DIR_INSTALL "${NAME_PACKAGE}/${NAME_PACKAGE_WITH_VERSION}")      # the dir to put installation
set(DIR_FIND    "${NAME_PACKAGE}/lib/${NAME_PACKAGE_WITH_VERSION}")  # the dir to put -installation.cmake, -config.cmake and -config-version.cmake


# Project - Modules


add_subdirectory("lizy1.kurisu")                                     # this module installs & exports NAME_LIB_MAIN
add_subdirectory("example")


# Find Package Support


include(CMakePackageConfigHelpers)
configure_package_config_file(                                       # generate a -config.cmake that includes -installation.cmake
    "${CMAKE_SOURCE_DIR}/config.cmake.in"                            # path config.cmake in
    "${CMAKE_BINARY_DIR}/${NAME_PACKAGE}-config.cmake"               # path config.cmake out
    INSTALL_DESTINATION "${DIR_FIND}/${NAME_PACKAGE}-config.cmake"   # path config.cmake install
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(                                    # generate the version file for the config file
    "${CMAKE_BINARY_DIR}/${NAME_PACKAGE}-config-version.cmake"       # path config-version.cmake out
    COMPATIBILITY AnyNewerVersion                                    # lib_main is compatible
)
install(                                                             # install -config.cmake & -config-version.cmake
    FILES
        "${CMAKE_BINARY_DIR}/${NAME_PACKAGE}-config.cmake"
        "${CMAKE_BINARY_DIR}/${NAME_PACKAGE}-config-version.cmake"
    DESTINATION "${DIR_FIND}"
)
