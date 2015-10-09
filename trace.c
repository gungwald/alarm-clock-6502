#include <stdio.h>

#include "trace.h"

static void open(void);
static void close(void);
static FILE *t;
static char mode[2] = {'w', '\0'};

static void open()
{
    t = fopen(TRACE_FILE_NAME, mode);
    if (t == NULL) {
        perror(TRACE_FILE_NAME);
    }
    mode[0] = 'a';
}

static void close()
{
    if (fclose(t) == EOF) {
        perror(TRACE_FILE_NAME);
    }
}

void trace_enter(char *func_name)
{
    open();
    fprintf(t, "Entering %s\n", func_name);
    close();
}

void trace_enter_str(char *func_name, char *str_param)
{
    open();
    fprintf(t, "Entering %s(%s)\n", func_name, str_param);
    close();
}

void trace_exit(char *func_name)
{
    open();
    fprintf(t, "Exiting %s\n", func_name);
    close();
}

void trace_ret_bool(char *func_name, bool bool_param)
{
    open();
    fprintf(t, "Exiting %s with %d\n", func_name, bool_param);
    close();
}

void trace_msg(const char *message)
{
    open();
    fprintf(t, "%s\n", message);
    close();
}
