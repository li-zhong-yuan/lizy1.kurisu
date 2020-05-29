cmake_minimum_required(VERSION 3.8)


set(DIR_INCLUDE_BUILD   "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DIR_INCLUDE_INSTALL "${DIR_INSTALL}/include")


# Lib - Main


add_library               ("${NAME_LIB_MAIN}" INTERFACE)
target_compile_features   ("${NAME_LIB_MAIN}" INTERFACE cxx_std_11)
target_include_directories("${NAME_LIB_MAIN}" INTERFACE "$<BUILD_INTERFACE:${DIR_INCLUDE_BUILD}>" "$<INSTALL_INTERFACE:${DIR_INCLUDE_INSTALL}>")


# Install


install(DIRECTORY "${DIR_INCLUDE_BUILD}" DESTINATION "${DIR_INSTALL}")
install(TARGETS "${NAME_LIB_MAIN}" EXPORT "${NAME_LIB_MAIN}-installation")
install(EXPORT "${NAME_LIB_MAIN}-installation" DESTINATION "${DIR_FIND}")
