#include <stdio.h>
#include <stdlib.h>
#include "freertps/freertps.h"
#include "controller/helper.h"
#include "controller/terminal.h"

int main(int argc, char **argv)
{
	char *cid = get_controller_ip();
	if (cid == NULL) {
		fprintf(stderr, "The controller has no IP, please check again\n");
		exit(-1);
	}

    TerminalInfo *info = init_info("127.0.0.1", 1, "ST", 1, 40000);
    Terminal *t = init_terminal(info);

	return 0;
}
