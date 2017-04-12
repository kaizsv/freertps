#ifndef __DAC_
#define __DAC_

#include <stdint.h>
#include "controller/terminal.h"

typedef struct __terminal_list TerminalList;
struct __terminal_list
{
    Terminal *terminal;
    TerminalList *next;
};

typedef struct __dac DAC;
struct __dac
{
    DAC *next;
    uint8_t did;

    TerminalList *sensors;
    TerminalList *actuators;
};

DAC *init_dac(uint8_t);

void free_dac(DAC *);

Terminal *get_dac_terminal_from_info(DAC *, TerminalInfo *);

void assign_terminal_to_dac(DAC *, Terminal *);

#endif // __DAC_
