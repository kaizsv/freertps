#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller/dac.h"

TerminalList *dac_sensors_or_actuators(DAC *, TerminalInfo *);
TerminalList *init_terminal_list(Terminal *);
void free_terminal_list(TerminalList *);
void free_terminal_list_all(TerminalList *);
void exec_terminal(TerminalList *);

void exec_terminals_of_dac(DAC *dac)
{
    printf("%d\n", dac->did);

    exec_terminal(dac->sensors);
    exec_terminal(dac->actuators);
}

void exec_terminal(TerminalList *terminal_list)
{
    Terminal *curr;
    while (terminal_list != NULL) {
        curr = terminal_list->terminal;
        curr->exec(curr);
        terminal_list = terminal_list->next;
    }
}

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
    free_terminal_list_all(dac->sensors);
    free_terminal_list_all(dac->actuators);
    free(dac);
}

Terminal *get_dac_terminal_from_info(DAC *dac, TerminalInfo *info)
{
    TerminalList *temp = dac_sensors_or_actuators(dac, info);

    while (temp != NULL) {
        Terminal *terminal = temp->terminal;
        if ((strcmp(terminal->info->cid, info->cid) == 0)
            && (terminal->info->did == info->did)
            && (strcmp(terminal->info->type, info->type) == 0)
            && (terminal->info->tid == info->tid)
            && (terminal->info->modbus_address == info->modbus_address))
        {
            return terminal;
        }

        temp = temp->next;
    }
    return NULL;
}

void assign_terminal_to_dac(DAC *dac, Terminal *terminal)
{
    if ((dac->sensors == NULL)
        && (dac->did == terminal->info->did)
        && (terminal->info->classification == SENSOR))
    {
        dac->sensors = init_terminal_list(terminal);
        return;
    }

    if ((dac->actuators == NULL)
        && (dac->did == terminal->info->did)
        && (terminal->info->classification == ACTUATOR))
    {
        dac->actuators = init_terminal_list(terminal);
        return;
    }

    TerminalList *temp = dac_sensors_or_actuators(dac, terminal->info);
    if ((temp == NULL) || (dac->did != terminal->info->did)) {
        // TODO: terminal type NONE
        printf("Assigned invalid terminal to dac.\r\n");
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = init_terminal_list(terminal);
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
    free_terminal(t_list->terminal);
    free(t_list);
}

void free_terminal_list_all(TerminalList *t_list)
{
    TerminalList *temp = t_list;
    while (t_list != NULL) {
        temp = temp->next;
        free_terminal_list(t_list);
        t_list = temp;
    }
}
