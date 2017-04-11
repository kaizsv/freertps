#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/dac.h"

TerminalList *dac_sensors_or_actuators(DAC *, TerminalInfo *);
TerminalList *init_terminal_list(Terminal *);
void free_terminal_list(TerminalList *);

DAC *init_dac(uint8_t did)
{
    DAC *dac = (DAC *) malloc(sizeof(DAC));
    dac->did = did;
    dac->sensors = NULL;
    dac->actuators = NULL;
    return dac;
}

void free_dac(DAC *dac)
{
    free_terminal_list(dac->sensors);
    free_terminal_list(dac->actuators);
    free(dac);
}

Terminal *get_dac_terminal_from_info(DAC *dac, TerminalInfo *info)
{
    TerminalList *temp = dac_sensors_or_actuators(dac, info);

    while (temp != NULL) {
        Terminal *terminal = temp->terminal;
        if ((strcmp(terminal->cid, info->cid) == 0)
            && (terminal->did == info->did)
            && (strcmp(terminal->type, info->type) == 0)
            && (terminal->tid == info->tid)
            && (terminal->modbus_address == info->modbus_address))
        {
            return temp;
        }

        temp = temp->next;
    }
    return NULL;
}

void assign_terminal_to_dac(DAC *dac, Terminal *terminal)
{
    if ((dac->sensors == NULL)
        && (terminal->info->classification == SENSOR))
    {
        dac->sensors = init_terminal_list(terminal);
        return;
    }

    if ((dac->actuators == NULL)
        && (terminal->info->classification == ACTUATOR))
    {
        dac->actuators = init_terminal_list(terminal);
        return;
    }

    TerminalList *temp = dac_sensors_or_actuators(dac, terminal->info);
    if (temp == NULL) {
        // TODO: terminal type NONE
    }

    while (temp != NULL) {
        temp = temp->next;
    }
    temp = init_terminal_list(terminal);
}

TerminalList *dac_sensors_or_actuators(DAC *dac, TerminalInfo *info)
{
    TerminalList *temp;
    if (info->classification == SENSOR) {
        temp = dac->sensors;
    } else if (info->classification == ACTUATOR) {
        temp = dac->actuators;
    } else {
        temp = NULL;
    }
    return temp;
}

TerminalList *init_terminal_list(Terminal *terminal)
{
    TerminalList *t_list = (TerminalList *) malloc(sizeof(TerminalList));
    t_list->terminal = terminal;
    t_list->next = NULL;
    return t_list;
}

void free_terminal_list(TerminalList *t_list)
{
    TerminalList *temp = t_list;
    while (t_list != NULL) {
        temp = temp->next;
        free(t_list);
        t_list = temp;
    }
}
