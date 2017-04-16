#ifndef __DEVICE_MANAGER_
#define __DEVICE_MANAGER_

#include "controller/dac.h"
#include "controller/terminal.h"

#define MAX_DEVICE_NUMBER 256

typedef struct __device_manager DeviceManager;
struct __device_manager
{
    DAC *dac_table;
    Terminal **terminal_table;
};

DeviceManager *init_device_manager();

void free_device_manager();

#endif // __DEVICE_MANAGER_
