#ifndef __DAC_
#define __DAC_

#include "controller/terminal.h"

typedef struct __terminal_list Terminal_List;
struct __terminal_list
{
    Terminal terminal;
    Terminal_List *next;
};

typedef struct __dac DAC;
struct __dac
{
    Terminal_List sensors;
    Terminal_List actuators;
    DAC *next;
};

DAC *init_dac();

#endif // __DAC_
