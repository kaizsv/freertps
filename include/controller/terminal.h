#ifndef __TERMINAL_
#define __TERMINAL_

#include <stdint.h>

#define SET_VALUE(TERMINAL, V_TYPE, VALUE)              \
            _Generic((VALUE),                           \
                int: set_value_INT,                     \
                float: set_value_FLOAT)(TERMINAL, VALUE)

#define GET_VALUE(TERMINAL, V_TYPE)             \
            get_value_##V_TYPE(TERMINAL)

#define GET_VALUE_STR(TERMINAL, V_TYPE)         \
            get_value_str_##V_TYPE(TERMINAL)


typedef struct __terminal_info TerminalInfo;
struct __terminal_info
{
    char *cid;
    uint8_t did;
    char *type;
    uint8_t tid;
    unsigned int modbus_address;

    enum {
        SENSOR,
        ACTUATOR,
        NONE
    } classification;
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

Terminal *init_terminal(char *, uint8_t, char *, uint8_t, unsigned int);

void free_terminal(Terminal *);

/*
    int function
*/
void set_value_INT(Terminal *, int);
int get_value_INT(Terminal *);
//char *get_value_str_INT(Terminal *);

/*
    float function
*/
void set_value_FLOAT(Terminal *, float);
float get_value_FLOAT(Terminal *);
//char *get_value_str_FLOAT(Terminal *);

#endif // __TERMINAL_
