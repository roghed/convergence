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

cmake_minimum_required(VERSION 3.24)

project(convergence LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(third_party/include)

add_subdirectory(src)

include(GNUInstallDirs)

install(TARGETS convergence
    CONFIGURATIONS Release)
install(DIRECTORY data
    DESTINATION ${CMAKE_INSTALL_DATADIR}/convergence
    CONFIGURATIONS Release)

set(CPACK_PACKAGE_NAME "Convergence")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "convergence")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jan Rogowski <janrogpl@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Program to visualize convergence of fixed point-iteration method")
set(CPACK_DEBIAN_PACKAGE_SECTION "math")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/roghed/convergence")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
