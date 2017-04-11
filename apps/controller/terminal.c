#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "controller/terminal.h"

void (*choose_terminal_function(char *))(Terminal *);
static void exec_ST_terminal(Terminal *);

TerminalInfo *init_info(char *cid, uint8_t did, char *type, uint8_t tid,
                        unsigned int address)
{
    TerminalInfo *info = (TerminalInfo *) malloc(sizeof(TerminalInfo));
    info->cid = cid;
    info->did = did;
    info->type = type;
    info->tid = tid;
    info->modbus_address = address;
    info->classification = (*type == 'S') ? SENSOR :
                           (*type == 'A') ? ACTUATOR : NONE;
    return info;
}

Terminal *init_terminal(TerminalInfo *info)
{
    Terminal *terminal = (Terminal *) malloc(sizeof(Terminal));
    terminal->info = info;
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
