add_executable(main-window
    main.cpp
    glfw_window.hpp glfw_window.cpp
    glfw_instance.hpp glfw_instance.cpp)
set_target_properties(main-window PROPERTIES OUTPUT_NAME convergence)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
get_property(importTargets DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("import targets: ${importTargets}")
target_link_libraries(main-window PRIVATE GLEW::GLEW glfw)
target_include_directories(main-window PRIVATE ${GLEW_INCLUDE_DIRS})
