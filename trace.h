#ifndef TRACE_H
#define TRACE_H

#ifdef TRACE

#include <stdbool.h>    /* bool */

#define TRACE_FILE_NAME "trace"

extern void trace_enter(char *func_name);
extern void trace_enter_str(char *func_name, char *str_param);
extern void trace_exit(char *func_name);
extern void trace_ret_bool(char *func_name, bool bool_param);
extern void trace_msg(const char *msg);

#define TRACE_ENTER(f)          trace_enter(f)
#define TRACE_ENTER_STR(f, s)   trace_enter_str(f, s)
#define TRACE_EXIT(f)           trace_exit(f)
#define TRACE_RET_BOOL(f, b)    trace_ret_bool(f, b)
#define TRACE_MSG(m)            trace_msg(m)

#else

#define TRACE_ENTER(f)
#define TRACE_ENTER_STR(f, s)
#define TRACE_EXIT(f);
#define TRACE_RET_BOOL(f, b)
#define TRACE_MSG(m)

#define trace_enter(f)
#define trace_enter_str(f, s)
#define trace_exit(f);
#define trace_ret_bool(f, b)
#define trace_msg(m)

#endif

#endif
