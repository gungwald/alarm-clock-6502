#include <stdio.h>  /* scanf */
#include <stdint.h> /* uint8_t */

#define CLOCK_FREQUENCY 1023000L
#define CYCLES_PER_NOOP 2
#define NOOPS_PER_SEC 511500

enum {
    ANTE_MERIDIEM, POST_MERIDIEM
} meridiem_t;

uint8_t curr_hour;
uint8_t curr_min;
meridiem_t curr_meridiem;

uint8_t alarm_hour;
uint8_t alarm_min;
meridiem_t alarm_meridiem;

void main(void)
{
    scanf("Current hour:%2ui", &curr_hour);
    scanf("Current minute:%2ui", &curr_min);
    scanf("Current AM/PM:%2s", &meridiem_input);
}

