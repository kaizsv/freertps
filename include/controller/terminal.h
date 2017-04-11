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

typedef struct __terminal_info TerminalInfo;
struct __terminal_info
{
    char *cid;
    uint8_t did;
    char *type;
    uint8_t tid;
    unsigned int modbus_address;
    Classification classification;
};

typedef struct __terminal_device Terminal;
struct __terminal_device
{
    TerminalInfo *info;

    enum { INT, FLOAT } v_type;
    union {
        int vi;
        float vf;
    } value;

    void (*exec)(Terminal *);
};

TerminalInfo *init_info(char *, uint8_t, char *, uint8_t, unsigned int);

Terminal *init_terminal(TerminalInfo *);

#endif // __TERMINAL_
