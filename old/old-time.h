#ifndef TWELVE_HOUR_CLOCK_H
#define TWELVE_HOUR_CLOCK_H

#include <stdint.h>     /* uint8_t */

typedef enum meridiem {
    ANTE_MERIDIEM, POST_MERIDIEM
} meridiem;

typedef struct {
    /* Bit fields */
    unsigned int seconds : 5; /* Stores 0..31, need 0..59 */
    unsigned int minutes : 6; /* Stores 0..63, need 0..59 */
    unsigned int hours   : 6; /* Stores 0..31, need 0..23 */
    unsigned int day     : 5; /* Stores 0..31, need 1..31 */
    unsigned int month   : 4; /* Stores 0..16, need 1..12 */
    unsigned int year    : 7; /* Stores 0..127, need 0..99 */
} unused_clock;

extern void read_time_interactively(struct tm *t);
extern bool load_system_time(struct tm *t);
extern void add_one_second(struct tm *t);
extern void print_12_hour_time(struct tm *t);
extern void reprint_12_hour_time(struct tm *t);

#endif

