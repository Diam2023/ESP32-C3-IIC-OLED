set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set(
        WIDGET_FOLDER
        "./src/widgets/"
)

set(
        LAYOUT_FOLDER
        "./src/layouts/"
)


set(
        WIDGETS
        ${WIDGET_FOLDER}text_widget.cc
        ${WIDGET_FOLDER}image_widget.cc
        ${WIDGET_FOLDER}graph_widget.cc
)

set(
        LAYOUTS
        ${LAYOUT_FOLDER}absolutely_layout.cc
        ${LAYOUT_FOLDER}list_layout.cc
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
        ${LAYOUTS}
        ${WIDGETS}
        INCLUDE_DIRS
        "./inc"
        "./inc/widgets"
        "./inc/layouts"
)
