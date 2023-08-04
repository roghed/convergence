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
