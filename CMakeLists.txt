set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

file(GLOB USER_SRCS ./src/*.cc)
file(GLOB USER_SUB_SRCS ./src/*/*.cc)

idf_component_register(SRCS ${USER_SRCS} ${USER_SUB_SRCS} INCLUDE_DIRS "./inc")
