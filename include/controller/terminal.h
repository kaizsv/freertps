#ifndef __TERMINAL_
#define __TERMINAL_

#include <stdint.h>

typedef enum __terminal_classification Classification;
enum __terminal_classification
{
    SENSOR,
    ACTUATOR,
    NONE
};

typedef struct __terminal_device Terminal;
struct __terminal_device
{
    char *cid;
    uint8_t did;
    char *type;
    uint8_t tid;
    unsigned int modbus_address;
    Classification classification;

    union {
        int vi;
        float vf;
    } value;

    void (*exec)(Terminal *);
};

Terminal *init_terminal(char *, uint8_t, char *, uint8_t, unsigned int);

#endif // __TERMINAL_
