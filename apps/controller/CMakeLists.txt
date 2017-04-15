add_library(irrigation 
    get_ip.c
    terminal.c
    dac.c
    exec_terminal.c
    )
freertps_add_executable(controller controller.c)
target_link_libraries(controller irrigation)
