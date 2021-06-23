cmake_minimum_required(VERSION 3.11)

# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "RelWithDebInfo")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

project (mcrelay
        VERSION 0.0.1
        DESCRIPTION "A simple bi-directional UDP multicast to unicast relay.  Useful for relaying multicast traffic between networks that otherwise wouldn't route multicast."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

set(Boost_USE_STATIC_LIBS on)
find_package(Boost 1.66 REQUIRED system)

find_package(Threads)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/udprelay.sh ${CMAKE_CURRENT_BINARY_DIR}/udprelay.sh COPYONLY)

add_subdirectory(src)

if(LINUX)
    add_subdirectory(systemd)
endif(LINUX)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CPACK_PACKAGE_CONTACT "Beau V.C. Bellamy <bellamy.beau@gmail.com>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libc6 (< 2.4)")
    set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
    set(CPACK_RPM_FILE_NAME "RPM-DEFAULT")
    set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/usr/lib/systemd" "/usr/lib/systemd/system" "/etc" "/usr" "/usr/lib" "/usr/bin")
    include(CPack)
endif()
