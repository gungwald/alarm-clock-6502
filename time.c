#include <stdio.h>      /* printf, scanf */
#include <stdbool.h>    /* bool */
#include <string.h>     /* strerror */
#include <time.h>       /* time_t, time, localtime */
#include <ctype.h>      /* toupper */
#include <errno.h>      /* errno */
#include <stdlib.h>     /* atoi */

#include "time.h"

#define TIME_ERR_RESULT         ((time_t) -1)
#define LOCALTIME_ERR_RESULT    NULL
#define ERR_MSG_SIZE            128

static const char *AM="AM";
static const char *PM="PM";

static char *to_upper_case(char *s);
static void set_err_msg(char *prefix, int errno);
static void copy_struct_tm(struct tm *dest, struct tm *src);
static const char *convert_24_hour_to_meridiem(uint8_t hours);
static uint8_t convert_12_hour_to_24_hour(uint8_t twelve_hour, char *meridiem);
static void convert_24_hour_to_12_hour(uint8_t twenty_four_hour, uint8_t *twelve_hour, char const **meridiem);

static char G_err_msg[ERR_MSG_SIZE];

void copy_struct_tm(struct tm *dest, struct tm *src)
{
    dest->tm_sec   = src->tm_sec;
    dest->tm_min   = src->tm_sec;
    dest->tm_hour  = src->tm_hour;
    dest->tm_mday  = src->tm_mday;
    dest->tm_mon   = src->tm_mon;
    dest->tm_year  = src->tm_year;
    dest->tm_wday  = src->tm_wday;
    dest->tm_yday  = src->tm_wday;
    dest->tm_isdst = src->tm_isdst;
}

static const char *convert_24_hour_to_meridiem(uint8_t hours)
{
    if (hours < 12) {
        return AM;
    }
    else {
        return PM;
    }
}

static uint8_t convert_12_hour_to_24_hour(uint8_t twelve_hour, char *meridiem)
{
    uint8_t twenty_four_hour;

    /* Default */
    twenty_four_hour = twelve_hour;

    /* Special cases */
    if (strcmp(meridiem, AM) == 0) {
        if (twelve_hour == 12) {
            twenty_four_hour = 0;
        }
    }
    else if (twelve_hour < 12) {
        twenty_four_hour = twelve_hour + 12;
    }
    return twenty_four_hour;
}

void convert_24_hour_to_12_hour(uint8_t twenty_four_hour, uint8_t *twelve_hour, char const **meridiem) 
{
    if (twenty_four_hour == 0) {
        *twelve_hour = 12;
    }
    else if (twenty_four_hour < 12) {
        *meridiem = AM;
    }
    else if (twenty_four_hour == 12) {
        *meridiem = PM;
    }
    else {
        *twelve_hour = twenty_four_hour - 12;
        *meridiem = PM;
    }
}

void set_err_msg(char *what_failed, int err_code)
{
    snprintf(G_err_msg, ERR_MSG_SIZE, "%s: %s", what_failed, strerror(err_code));
}

bool load_system_time(struct tm *t)
{
    time_t now;
    struct tm *now_breakdown;
    bool success = false;

    if (time(&now) != TIME_ERR_RESULT) {
        if ((now_breakdown = localtime(&now)) != LOCALTIME_ERR_RESULT) {
            copy_struct_tm(t, now_breakdown);
            success = true;
        }
        else {
            perror("Localtime failed");
        }
    }
    else {
        perror("Time function failed");
    }
    return success;
}

char *to_upper_case(char *s)
{
    size_t i;

    for (i = 0; s[i] != '\0'; ++i) {
        s[i] = toupper(s[i]);
    }
    return s;
}

void read_time_interactively(struct tm *t)
{
    char line[4];
    int8_t hour;
    int8_t min;

    printf("Hour:");
    hour = atoi(fgets(line, sizeof(line), stdin));
    printf("Minute:");
    min = atoi(fgets(line, sizeof(line), stdin));
    printf("AM or PM:");
    fgets(line, sizeof(line), stdin);

    t->tm_hour = convert_12_hour_to_24_hour(hour, line);
    t->tm_min = min;
    t->tm_sec = 0;
}

void print_12_hour_time(struct tm *t)
{
    uint8_t hour;
    const char *meridiem;

    convert_24_hour_to_12_hour(t->tm_hour, &hour, &meridiem);
    printf("%2hu:%02d:%02d %2s", hour, t->tm_min, t->tm_sec, meridiem);
}

void reprint_12_hour_time(struct tm *t)
{
    printf("\b\b\b\b\b\b\b\b\b\b\b");
    print_12_hour_time(t);
}

