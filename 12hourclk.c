#include <stdio.h>      /* printf, scanf */
#include <stdbool.h>    /* bool */
#include <string.h>     /* strerror */
#include <time.h>       /* time_t, time, localtime */
#include <ctype.h>      /* toupper */
#include <errno.h>      /* errno */

#include "12hourclk.h"

#define TIME_ERR_RESULT         ((time_t) -1)
#define LOCALTIME_ERR_RESULT    NULL
#define ERR_MSG_SIZE            128

static void set_err_msg(char *prefix, int errno);

static char G_err_msg[ERR_MSG_SIZE];

static char *meridiem_text(meridiem_t m)
{
    if (m == ANTE_MERIDIEM) {
        return "am";
    }
    else {
        return "pm";
    }
}

bool set_clock(twleve_hour_clock_t *clock, struct tm *t)
{
    clock->seconds = t->tm_sec;
    clock->minutes = t->tm_min;
    if (t->tm_hour == 0) {
        clock->hours = 12;
        clock->meridiem = ANTE_MERIDIEM;
    }
    else if (t->tm_hour < 12) {
        clock->meridiem = ANTE_MERIDIEM;
    }
    else if (t->tm_hour == 12) {
        clock->meridiem = POST_MERIDIEM;
    }
    else {
        clock->hours = t->tm_hour - 12;
        clock->meridiem = POST_MERIDIEM;
    }
    return true;
}


void set_err_msg(char *what_failed, int err_code)
{
    snprintf(G_err_msg, ERR_MSG_SIZE, "%s: %s", what_failed, strerror(err_code));
}

bool load_system_time(twleve_hour_clock_t *clock)
{
    time_t now;
    bool is_successful = false; /* It will not be successful until it is. */
    struct tm *curr_time;

    if (time(&now) != TIME_ERR_RESULT)
        if ((curr_time = localtime(&now)) != LOCALTIME_ERR_RESULT)
            is_successful = set_clock(clock, curr_time);
        else 
            set_err_msg("Localtime function failed", errno);
    else
        set_err_msg("Time function failed", errno);
    return is_successful;
}

void read_interactively(twleve_hour_clock_t *clock)
{
    char meridiem_input[3];

    printf("Hour:");
    scanf("%2ui", &(clock->hours));
    printf("Minute:");
    scanf("%2ui", &(clock->minutes));
    printf("AM or PM:");
    scanf("%2s", meridiem_input);
    clock->seconds = 0;
    if (toupper(meridiem_input[0]) == 'A') {
        clock->meridiem = ANTE_MERIDIEM;
    }
    else {
        clock->meridiem = POST_MERIDIEM;
    }
}

void add_one_second(twleve_hour_clock_t *clock)
{
    if (clock->seconds < 59) {
        ++(clock->seconds);
    }
    else {
        clock->seconds = 0;
        if (clock->minutes < 59) {
            ++(clock->minutes);
        }
        else {
            clock->minutes = 0;
            if (clock->hours < 11) {
                ++(clock->hours);
            }
            else if (clock->hours == 11) {
                ++(clock->hours);
                if (clock->meridiem == ANTE_MERIDIEM) {
                    clock->meridiem = POST_MERIDIEM;
                }
                else {
                    clock->meridiem = ANTE_MERIDIEM;
                }
            }
            else {
                clock->hours = 1;
            }
        }
    }
}

void add_seconds(twleve_hour_clock_t *clock, uint8_t seconds)
{
    uint16_t sum;
    uint16_t minutes_carry;
    uint16_t hours_carry;
    
    sum = ((uint16_t) clock->seconds) + ((uint16_t) seconds);
    if (sum >= 60) {
        minutes_carry = sum / 60;
        clock->seconds = sum % 60;

        sum = ((uint16_t) clock->minutes) + minutes_carry;
        if (sum >= 60) {
            hours_carry = sum / 60;
            clock->minutes = sum % 60;

            sum = ((uint16_t) clock->hours) + hours_carry;
            if (sum >= 12) {
            }
        }
        else {
            clock->minutes = sum;
        }
    }
    else {
        clock->seconds = sum;
    }
}

void print_time(twleve_hour_clock_t *clock)
{
    printf("%2u:%02u:%02u %2s", clock->hours, clock->minutes, clock->seconds, meridiem_text(clock->meridiem));
}

void reprint_time(twleve_hour_clock_t *clock)
{
    printf("\b\b\b\b\b\b\b\b\b\b\b");
    print_time(clock);
}

