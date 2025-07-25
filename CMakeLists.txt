cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(OpenSNT VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MODULE_NAME opensnt)
#set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_INCLUDEDIR include)

# set environmental variables
file(READ "settings.env" ENV_CONTENTS)
string(REGEX MATCH "CODE_VERSION=([^\n\r]*)" _ ${ENV_CONTENTS})
string(REGEX REPLACE ".*CODE_VERSION=([^\n\r]*).*" "\\1" CODE_VERSION "${_}")

# set preprocessor flags
add_compile_definitions(CODE_VERSION="${CODE_VERSION}")
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/settings.h.in
    ${CMAKE_BINARY_DIR}/settings.h
)

option(COMPILE_EXS "Compile EXS module" ON)
option(COMPILE_VAL "Compile VAL module" ON)
option(COMPILE_PUQ "Compile PUQ module" ON)
option(COMPILE_DIP "Compile DIP module" ON)

set(COMPILE_PUQ_MAGNITUDE "array" CACHE STRING "Set the type of magnitude in PUQ module (array, value)")
if(COMPILE_PUQ_MAGNITUDE STREQUAL "array")
    add_compile_definitions(COMPILE_PUQ_MAGNITUDE_ARRAY)
elseif(COMPILE_PUQ_MAGNITUDE STREQUAL "value")
    add_compile_definitions(COMPILE_PUQ_MAGNITUDE_VALUE)
else()
    message(FATAL_ERROR "Invalid COMPILE_PUQ_MAGNITUDE: ${COMPILE_PUQ_MAGNITUDE}. Must be 'array' or 'value'.")
endif()

# compile libraries and executables
###################################

message("SCientific Numerical Tools (OpenSNT)")
message("Code version: ${CODE_VERSION}")

add_subdirectory(src)        # build dip-cpp library
add_subdirectory(exec)       # build executables
add_subdirectory(gtest)      # build gtest executable

# create cmake export files
###########################

include(CMakePackageConfigHelpers)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/${MODULE_NAME}-config.cmake.in
  	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config.cmake"
  	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}
	PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
    	VERSION ${CODE_VERSION}
    	COMPATIBILITY AnyNewerVersion
)

# install files
###############
	
install(DIRECTORY src/
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_NAME}
	FILES_MATCHING PATTERN "*.h")
	
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}
)

install(EXPORT TargetsOpenSNT
        FILE ${MODULE_NAME}-targets.cmake
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}"
)

