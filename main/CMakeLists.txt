set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set(
        WIDGET_FOLDER
        "./src/widgets/"
)

set(
        WIDGETS
        ${WIDGET_FOLDER}text_widget.cc
        ${WIDGET_FOLDER}image_widget.cc
        ${WIDGET_FOLDER}list_widget.cc
        ${WIDGET_FOLDER}graph_widget.cc
)

idf_component_register(
        SRCS
        "main.cc"
        "./src/oled_device.cc"
        "./src/object.cc"
        "./src/paint.cc"
        "./src/page.cc"
        "./src/window.cc"
        "./src/layout.cc"
        "./src/widget.cc"
        "./src/layouts/absolutely_layout.cc"
        "./src/layouts/list_layout.cc"
        ${WIDGETS}
        INCLUDE_DIRS
        "./inc"
        "./inc/widgets"
        "./inc/layouts"
)
