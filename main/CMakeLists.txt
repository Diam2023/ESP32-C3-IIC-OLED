set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(WIDGET_SRC "./src/widgets")
set(WIDGET_HEADER "./inc/widgets")

set(LAYOUT_SRC "./src/layouts")
set(LAYOUT_HEADER "./inc/layouts")

file(GLOB_RECURSE COMPONENT_SRCS "./main.cc" "./src/*.cc" ${LAYOUT_SRC}/*.cc ${WIDGET_SRC}/*.cc)

set(COMPONENT_ADD_INCLUDEDIRS 
    "./inc"
    ${LAYOUT_HEADER}
    ${WIDGET_HEADER}
    )

register_component()
