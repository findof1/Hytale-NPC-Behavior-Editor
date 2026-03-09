set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    "${CMAKE_SOURCE_DIR}/Editor/Include"
)

file(GLOB_RECURSE ENGINE_SRC "${CMAKE_SOURCE_DIR}/Editor/src/*.cpp")

add_executable(Editor
    ${ENGINE_SRC}
    "${CMAKE_SOURCE_DIR}/Editor/Include/nodeWidgets.hpp"
)

#target_compile_definitions(Editor PRIVATE NDEBUG)

target_link_libraries(Editor PRIVATE
    Qt6::Widgets
)