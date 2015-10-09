#ifndef TWELVE_HOUR_CLOCK_H
#define TWELVE_HOUR_CLOCK_H

#include <stdint.h>     /* uint8_t */
#include <time.h>       /* time_t */

extern void read_time_interactively(struct tm *t);
extern bool load_system_time(struct tm *t);
extern void add_one_second(struct tm *t);
extern void print_12_hour_time(struct tm *t);
extern void reprint_12_hour_time(struct tm *t);

#endif

