#[[ Copyright (C) 2023 Jan Rogowski

This file is part of Convergence.

Convergence is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

Convergence is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Convergence. If not, see <https://www.gnu.org/licenses/>.]]

file(GLOB data_files
    RELATIVE ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_SOURCE_DIR}/data/*)
list(TRANSFORM data_files
    PREPEND ${CMAKE_SOURCE_DIR}/data/
    OUTPUT_VARIABLE src_dir_data_files)
list(TRANSFORM data_files
    PREPEND ${CMAKE_BINARY_DIR}/data/
    OUTPUT_VARIABLE bin_dir_data_files)

add_custom_command(
    OUTPUT  ${bin_dir_data_files}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
    DEPENDS ${src_dir_data_files})

add_executable(convergence
    main.cpp
    application.hpp application.cpp
    main_window.hpp main_window.cpp
    input_window.hpp input_window.cpp
    mouse_drag.hpp mouse_drag.cpp
    resource_locator.hpp resource_locator.cpp
    ${bin_dir_data_files})

if (MSVC)
    target_compile_options(convergence PRIVATE /W4 /bigobj)
else()
    target_compile_options(convergence PRIVATE -Wall -Wextra)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
    set_target_properties(convergence PROPERTIES WIN32_EXECUTABLE TRUE)
    target_compile_definitions(convergence PRIVATE HAS_WINMAIN_ENTRY_POINT)
endif()

set_target_properties(convergence
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SFML REQUIRED COMPONENTS graphics window system)
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(convergence
    PRIVATE sfml-system sfml-window sfml-graphics Boost::system Boost::filesystem)

# common CPack options
set(CPACK_PACKAGE_NAME "Convergence")
set(CPACK_PACKAGE_VENDOR "Jan Rogowski")
set(CPACK_PACKAGE_DESCRIPTION "Program to visualize convergence of the fixed-point iteration method")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/roghed/convergence")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

# DEB generator only CPack options
include(GNUInstallDirs)
set(CPACK_GENERATOR DEB)
install(TARGETS convergence
    CONFIGURATIONS Release)
install(DIRECTORY data
    DESTINATION ${CMAKE_INSTALL_DATADIR}/convergence
    CONFIGURATIONS Release)
set(CPACK_DEBIAN_PACKAGE_NAME "convergence")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jan Rogowski <janrogpl@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "math")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
