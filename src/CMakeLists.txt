add_executable(main-window
    main.cpp
    application_window.hpp application_window.cpp)
set_target_properties(main-window PROPERTIES OUTPUT_NAME convergence)
find_package(SFML REQUIRED COMPONENTS graphics window system)
get_property(importTargets DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("import targets: ${importTargets}")
target_link_libraries(main-window PRIVATE sfml-system sfml-window sfml-graphics)
