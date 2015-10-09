#include <string.h>     /* size_t */

#include "prodos.h"
#include "symbols.h"
#include "trace.h"

/*
char *turn_on_high_bits(char *s)
{
    size_t i = 0;

    for ( ; s[i] != '\0'; ++i) {
        s[i] |= '\x80';
    }
    return s;
}
*/

bool run_basic_system_command(const char *command)
{
    size_t i = 0;
    bool finished_successfully = false;

    TRACE_ENTER_STR("run_basic_system_command", (char *) command);
    for ( ; command[i] != '\0'; ++i) {
        /* Set the high bit and copy into the input buffer. */
        INPBUF[i] = command[i] | '\x80';
    }
    /* Append carriage return with high bit set. */
    INPBUF[i] = '\x8d';
    TRACE_MSG("About to JSR DOSCMD");
    asm("JSR %w", DOSCMD);  /* %w is for a "word" value. */
    asm("BIT %w", KBDSTRB); /* Clear strobe. */

    /* If the command failed, the carry flag is set and register A has the
       error code. */
    asm("BCS %g", doscmd_error_handler);
    finished_successfully = true;
    goto finished;

    doscmd_error_handler:
    TRACE_MSG("About to JSR PRERR");
    asm("JSR %w", PRERR);   /* Prints the error. */
    asm("CLC");             /* Required or bad stuff happens. */

    finished:
    TRACE_RET_BOOL("run_basic_system_command", finished_successfully);
    return finished_successfully;
}

