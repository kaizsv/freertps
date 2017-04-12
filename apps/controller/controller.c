#include <stdio.h>
#include <stdlib.h>
#include "freertps/freertps.h"
#include "controller/helper.h"
#include "controller/terminal.h"
#include "controller/dac.h"

int main(int argc, char **argv)
{
    char *cid = get_controller_ip();
    if (cid == NULL) {
        fprintf(stderr, "The controller has no IP, please check again\n");
        exit(-1);
    }

    DAC *dac = init_dac(1);
    Terminal *t1 = init_terminal("127.0.0.1", 1, "ST", 1, 40000);
    Terminal *t2 = init_terminal("127.0.0.1", 1, "ST", 2, 40001);
    Terminal *t3 = init_terminal("127.0.0.1", 1, "AW", 3, 40002);
    assign_terminal_to_dac(dac, t1);
    assign_terminal_to_dac(dac, t2);
    assign_terminal_to_dac(dac, t3);
    free_dac(dac);

    free(cid);
    return 0;
}
