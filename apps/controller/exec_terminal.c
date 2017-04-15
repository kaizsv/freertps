#include <string.h>
#include <stdio.h>
#include "controller/exec_terminal.h"

void choose_terminal_function(Terminal *t)
{
    if (strcmp(t->info->type, "ST") == 0) {
        // air temperature
        t->v_type = FLOAT;
        SET_VALUE(t, t->v_type, 0.0f);
        t->exec = exec_ST_terminal;
    } else if (strcmp(t->info->type, "SH") == 0) {
        // air humidity
        t->v_type = FLOAT;
        SET_VALUE(t, t->v_type, 0.0f);
        t->exec = exec_SH_terminal;
    } else if (strcmp(t->info->type, "SHE") == 0) {
        // soil temperature
    } else if (strcmp(t->info->type, "SPH") == 0) {
        // soil ph
    } else if (strcmp(t->info->type, "SI") == 0) {
        // sunlight
    } else if (strcmp(t->info->type, "AW") == 0) {
        // irrigation actuator
        t->v_type = INT;
        SET_VALUE(t, t->v_type, 0);
        t->exec = exec_AW_terminal;
    } else {
        // TODO
    }
}

void exec_ST_terminal(Terminal *t)
{
    printf("%d %s %d\n", t->info->did, t->info->type, t->info->tid);
}

void exec_SH_terminal(Terminal *t)
{
    printf("%d %s %d\n", t->info->did, t->info->type, t->info->tid);
}

void exec_AW_terminal(Terminal *t)
{
    printf("%d %s %d\n", t->info->did, t->info->type, t->info->tid);
}
