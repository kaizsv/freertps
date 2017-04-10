#include <stdio.h>
#include <stdlib.h>
#include "controller/dac.h"

DAC *init_dac()
{
    DAC *dac = (DAC *) malloc(sizeof(DAC));
    return dac;
}
