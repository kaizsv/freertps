#include <stdio.h>
#include "freertps/freertps.h"
#include "controller/helper.h"

int main(int argc, char **argv)
{
	char *cid = get_controller_ip();
	if (cid == NULL) {
		fprintf(stderr, "The controller has no IP, please check again\n");
		exit(-1);
	}

	return 0;
}
