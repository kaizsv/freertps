#include <stdlib.h>
#include <stdio.h>
#include "controller/terminal.h"
#include "controller/exec_terminal.h"

#define MAX_VALUE_DIGITS 10

Terminal *init_terminal(char *cid, uint8_t did, char *type, uint8_t tid,
                        unsigned int address)
{
    // initial terminal information
    TerminalInfo *info = (TerminalInfo *) malloc(sizeof(TerminalInfo));
    info->cid = cid;
    info->did = did;
    info->type = type;
    info->tid = tid;
    info->modbus_address = address;
    // if first charactor of type is 'S', then it is sensor
    // else 'A' for actuator
    info->classification = (*type == 'S') ? SENSOR :
                           (*type == 'A') ? ACTUATOR : NONE;

    // initial terminal node
    Terminal *terminal = (Terminal *) malloc(sizeof(Terminal));
    terminal->info = info;
    choose_terminal_function(terminal);

    return terminal;
}

void free_terminal(Terminal *terminal)
{
    free(terminal->info);
    free(terminal);
}

void set_value_INT(Terminal *terminal, int vi)
{
    terminal->value.vi = vi;
}

void set_value_FLOAT(Terminal *terminal, float vf)
{
    terminal->value.vf = vf;
}

int get_value_INT(Terminal *terminal)
{
    return terminal->value.vi;
}

float get_value_FLOAT(Terminal *terminal)
{
    return terminal->value.vf;
}

/*
char *get_value_str_INT(Terminal *terminal)
{
    // TODO: 10 digits is enough for sensor value,
    //       but if the digits of value is too long, need an efficient
    //       function to cast int to string.
    char buf[MAX_VALUE_DIGITS];
    snprintf(buf, MAX_VALUE_DIGITS, "%d", terminal->value.vi);
    return buf;
}

char *get_value_str_FLOAT(Terminal *terminal)
{
    // TODO: 10 digits is enough for sensor value,
    //       but if the digits of value is too long, need an efficient
    //       function to cast float to string.
    char buf[MAX_VALUE_DIGITS];
    snprintf(buf, MAX_VALUE_DIGITS, "%.2f", terminal->value.vf);
    return buf;
}
*/
