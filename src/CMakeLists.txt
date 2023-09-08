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
    target_compile_options(convergence PRIVATE /W4)
else()
    target_compile_options(convergence PRIVATE -Wall -Wextra)
endif()

set_target_properties(convergence
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (MSVC)
  target_compile_options(convergence PRIVATE /bigobj)
else ()
  target_compile_options(convergence PRIVATE -Wa,-mbig-obj)
endif ()

find_package(SFML REQUIRED COMPONENTS graphics window system)
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(convergence
    PRIVATE sfml-system sfml-window sfml-graphics Boost::system Boost::filesystem)
