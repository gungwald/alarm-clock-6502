#ifndef TWELVE_HOUR_CLOCK_H
#define TWELVE_HOUR_CLOCK_H

#include <stdint.h>     /* uint8_t */

typedef enum {
    ANTE_MERIDIEM, POST_MERIDIEM
} meridiem_t;

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    meridiem_t meridiem;
} twleve_hour_clock_t;

extern void read_interactively(twleve_hour_clock_t *clock);
extern bool load_system_time(twleve_hour_clock_t *clock);
extern void add_one_second(twleve_hour_clock_t *clock);
extern void add_seconds(twleve_hour_clock_t *clock, uint8_t seconds);
extern void print_time(twleve_hour_clock_t *clock);
extern void reprint_time(twleve_hour_clock_t *clock);

#endif

