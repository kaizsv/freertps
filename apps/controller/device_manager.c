#include <stdlib.h>
#include "controller/device_manager.h"

DeviceManager *init_device_manager()
{
    DeviceManager *dm = (DeviceManager *) malloc(sizeof(DeviceManager));
    dm->dac_table = NULL;
    dm->terminal_table = NULL;
    return dm;
}

void free_device_manager(DeviceManager *dm)
{
    free(dm->dac_table);
}
