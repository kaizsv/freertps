add_library(irrigation 
    helper.c
    terminal.c
    dac.c
    )
freertps_add_executable(controller controller.c)
target_link_libraries(controller irrigation)
