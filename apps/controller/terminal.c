#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "controller/terminal.h"

#define MAX_VALUE_DIGITS 10

static void exec_ST_terminal(Terminal *);

void choose_terminal_function(Terminal *t)
{
    if (strcmp(t->info->type, "ST") == 0) {
        // air temperature
        t->v_type = FLOAT;
        SET_VALUE(t, t->v_type, 0.0f);
        t->exec = exec_ST_terminal;
    } else if (strcmp(t->info->type, "SH") == 0) {
        // air humidity
    } else if (strcmp(t->info->type, "SHE") == 0) {
        // soil temperature
    } else if (strcmp(t->info->type, "SPH") == 0) {
        // soil ph
    } else if (strcmp(t->info->type, "SI") == 0) {
        // sunlight
    } else if (strcmp(t->info->type, "AW") == 0) {
        // irrigation actuator
    } else {
        // TODO
    }
}

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

static void exec_ST_terminal(Terminal *t)
{
    printf("TEST\r\n");
}
