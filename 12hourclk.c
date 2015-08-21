#include <stdio.h>      /* printf, scanf */
#include <ctype.h>      /* toupper */
#include "12hourclk.h"

static char *meridiem_text(meridiem_t m)
{
    if (m == ANTE_MERIDIEM) {
        return "am";
    }
    else {
        return "pm";
    }
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

