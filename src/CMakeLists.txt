add_executable(main-window
    main.cpp
    application_window.hpp application_window.cpp
    mouse_drag.hpp mouse_drag.cpp
    shaders/iterate_frag.glsl)
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/iterate_frag.glsl
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/shaders/iterate_frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/shaders/iterate_frag.glsl
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/iterate_frag.glsl)
set_target_properties(main-window PROPERTIES OUTPUT_NAME convergence)
find_package(SFML REQUIRED COMPONENTS graphics window system)
get_property(importTargets DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("import targets: ${importTargets}")
target_link_libraries(main-window PRIVATE sfml-system sfml-window sfml-graphics)
