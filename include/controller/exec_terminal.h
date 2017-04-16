#ifndef __EXEC_TERMINAL_
#define __EXEC_TERMINAL_

#include "controller/terminal.h"

void choose_terminal_function(Terminal *);

void exec_ST_terminal(Terminal *);

void exec_SH_terminal(Terminal *);

void exec_AW_terminal(Terminal *);

#endif // __EXEC_TERMINAL_
