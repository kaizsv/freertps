#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "controller/terminal.h"

void (*choose_terminal_function(char *))(Terminal *);
static void exec_ST_terminal(Terminal *);

Terminal *init_terminal(char *cid, uint8_t did, char *type, uint8_t tid,
                        unsigned int address)
{
    Terminal *terminal = (Terminal *) malloc(sizeof(Terminal));
    terminal->cid = cid;
    terminal->did = did;
    terminal->type = type;
    terminal->tid = tid;
    terminal->modbus_address = address;
    terminal->classification = (*type == 'S') ? SENSOR :
                               (*type == 'A') ? ACTUATOR : NONE;
    terminal->exec = choose_terminal_function(type);
    return terminal;
}

void (*choose_terminal_function(char *type))(Terminal *)
{
    if (strcmp(type, "ST") == 0) {
        // air temperature
        return exec_ST_terminal;
    } else if (strcmp(type, "SH") == 0) {
        // air humidity
    } else if (strcmp(type, "SHE") == 0) {
        // soil temperature
    } else if (strcmp(type, "SPH") == 0) {
        // soil ph
    } else if (strcmp(type, "SI") == 0) {
        // sunlight
    } else if (strcmp(type, "AW") == 0) {
        // irrigation actuator
    } else {
    }
    return exec_ST_terminal;
}

static void exec_ST_terminal(Terminal *t)
{
    printf("TEST\r\n");
}
