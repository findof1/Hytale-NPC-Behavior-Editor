set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    "${CMAKE_SOURCE_DIR}/Editor/Include"
    "${CMAKE_SOURCE_DIR}/Editor/External"
)

file(GLOB_RECURSE ENGINE_SRC "${CMAKE_SOURCE_DIR}/Editor/src/*.cpp")

add_executable(Editor
    ${ENGINE_SRC}
    "${CMAKE_SOURCE_DIR}/Editor/Include/projectSelector.hpp" #for AUTOMOC
    "${CMAKE_SOURCE_DIR}/Editor/Include/nodeWidgets.hpp" #for AUTOMOC
)

set_target_properties(Editor PROPERTIES WIN32_EXECUTABLE ON)
#target_compile_definitions(Editor PRIVATE NDEBUG)

target_link_libraries(Editor PRIVATE
    Qt6::Widgets
)