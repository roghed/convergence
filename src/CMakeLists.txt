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

add_executable(convergence
    main.cpp
    application.hpp application.cpp
    main_window.hpp main_window.cpp
    input_window.hpp input_window.cpp
    mouse_drag.hpp mouse_drag.cpp
    shaders/iterate_frag.glsl
    ${CMAKE_SOURCE_DIR}/resources/UbuntuMono-Regular.ttf)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/iterate_frag.glsl
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/shaders/iterate_frag.glsl 
            ${CMAKE_CURRENT_BINARY_DIR}/shaders/iterate_frag.glsl
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/iterate_frag.glsl)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/UbuntuMono-Regular.ttf
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/UbuntuMono-Regular.ttf 
                ${CMAKE_CURRENT_BINARY_DIR}/resources/UbuntuMono-Regular.ttf
	MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/resources/UbuntuMono-Regular.ttf)
message(${CMAKE_SOURCE_DIR}/resources/UbuntuMono-Regular.ttf)
find_package(SFML REQUIRED COMPONENTS graphics window system)
target_link_libraries(convergence PRIVATE sfml-system sfml-window sfml-graphics)
