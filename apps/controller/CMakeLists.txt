add_library(helper helper.c)
freertps_add_executable(controller controller.c)
target_link_libraries(controller helper)
