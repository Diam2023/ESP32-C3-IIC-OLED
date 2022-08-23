set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

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
        "./src/widgets/text_widget.cc"
        "./src/layouts/absolutely_layout.cc"
        INCLUDE_DIRS
        "./inc"
        "./inc/widgets"
        "./inc/layouts"
)
