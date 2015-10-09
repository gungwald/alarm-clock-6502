#ifndef NOSLOTCLOCK_H
#define NOSLOTCLOCK_H

#include <stdbool.h>

extern bool load_driver(void);
extern struct tm *read_time(struct tm *t);

#endif

