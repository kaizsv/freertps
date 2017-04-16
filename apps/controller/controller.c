#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "freertps/freertps.h"
#include "controller/get_ip.h"
#include "controller/terminal.h"
#include "controller/dac.h"
#include "controller/device_manager.h"

#define USAGE "usage: ./controller [<rpc_ip>]\n"

// SIGINT handler
static volatile sig_atomic_t sigint_status;
static void sigint_handler(int signo)
{
    sigint_status = signo;
}

// dac list
typedef struct __dac_list DACList;
struct __dac_list
{
    DACList *next;
    DAC *dac;
};

DACList *init_dac_list(DAC *);
void append_dac_to_dac_list(DACList **, DAC *);
void free_dac_list(DACList *);
void free_dac_list_all(DACList *);
// dac list

// scanning if there are new device or removing device
void scann_dac_and_terminal(DACList **, char *);

void scann_dac_and_terminal(DACList **dac_list, char *cid)
{
    DAC *dac = init_dac(1);
    Terminal *t1 = init_terminal(cid, 1, "ST", 1, 40000);
    Terminal *t2 = init_terminal(cid, 1, "SH", 2, 40001);
    Terminal *t3 = init_terminal(cid, 1, "AW", 3, 40002);
    assign_terminal_to_dac(dac, t1);
    assign_terminal_to_dac(dac, t2);
    assign_terminal_to_dac(dac, t3);
    DAC *dac2 = init_dac(2);
    Terminal *t21 = init_terminal(cid, 2, "ST", 1, 40000);
    assign_terminal_to_dac(dac2, t21);

    append_dac_to_dac_list(dac_list, dac);
    append_dac_to_dac_list(dac_list, dac2);
}

int main(int argc, char **argv)
{
    /*
    // rpc ip
    if (argc < 2) {
        fprintf(stderr, USAGE);
        exit(-1);
    }
    char *rpc_ip = argv[1];
    */

    // set sigint
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(-1);
    }

    // get controller ip
    char *cid = get_controller_ip();
    if (cid == NULL) {
        fprintf(stderr, "The controller has no IP, please check again\n");
        exit(-1);
    }

    // init dac list
    DACList *dac_list = NULL;
    DeviceManager *dm = init_device_manager();
    scann_dac_and_terminal(&dac_list, cid);

    // start main loop
    DAC *current_dac;
    DACList *current_dac_list;
    // main loop can be stop by SIGINT
    while (!sigint_status) {
        current_dac_list = dac_list;
        while (current_dac_list != NULL) {
            current_dac = current_dac_list->dac;
            exec_terminals_of_dac(current_dac);

            current_dac_list = current_dac_list->next;
        }
    }

    // free all memory
    free_dac_list_all(dac_list);
    free(cid);

    return 0;
}

DACList *init_dac_list(DAC *dac)
{
    DACList *dac_list = (DACList *) malloc(sizeof(DACList));
    dac_list->dac = dac;
    dac_list->next = NULL;
    return dac_list;
}

void append_dac_to_dac_list(DACList **p_dac_list, DAC *dac)
{
    DACList *temp = init_dac_list(dac);

    if (*p_dac_list == NULL) {
        *p_dac_list = temp;
        return;
    }

    while ((*p_dac_list)->next != NULL) {
        p_dac_list = &(*p_dac_list)->next;
    }
    (*p_dac_list)->next = temp;
}

void free_dac_list(DACList *dac_list)
{
    free_dac(dac_list->dac);
    free(dac_list);
}

void free_dac_list_all(DACList *dac_list)
{
    DACList *temp = dac_list;
    while (dac_list != NULL) {
        temp = temp->next;
        free_dac_list(dac_list);
        dac_list = temp;
    }
}
