#include <stdio.h>      /* fprintf, stderr */
#include <stdbool.h>    /* bool, true, false */
#include <stdint.h>     /* uint8_t */
#include <time.h>       /* struct tm */

#include "noslotclock.h"
#include "prodos.h"
#include "trace.h"

#define NSC_STRING_RESULT_ADDR  0x0280  /* String result, Ends at 0x0291      */
#define NSC_STRING_RESULT_LEN       12  /* The length of the above result     */
#define NSC_UPDATE_SUB_ADDR     0x030B  /* Start address of update subroutine */

typedef struct {
    uint8_t year;               /* 0..99 */
    uint8_t month;              /* 1..12 */
    uint8_t day_of_month;       /* 1..31 */
    uint8_t day_of_week;        /* 1..7  */
    uint8_t hour;               /* 0..23 */
    uint8_t min;                /* 0..59 */
    uint8_t sec;                /* 0..59 */
    uint8_t hundredths_of_sec;  /* 0..99 */
} no_slot_clock_time_t;

static const no_slot_clock_time_t *nsc = (no_slot_clock_time_t *) 0x0303;
static const char *nsc_absent_addr = (char *) 0x0304;

static bool is_nsc_absent(void);
static void read_time_from_nsc(void);

static void read_time_from_nsc()
{
    TRACE_ENTER("read_time_from_nsc");
    asm("jsr %w", NSC_UPDATE_SUB_ADDR);
    TRACE_EXIT("read_time_from_nsc");
}

/**
 * load_driver must be called first.
 */
static bool is_nsc_absent()
{
    TRACE_ENTER("is_nsc_absent");
    read_time_from_nsc();
    TRACE_EXIT("is_nsc_absent");
    return nsc_absent_addr[0] == NULL;
}

bool load_driver()
{
    bool status = false;

    TRACE_ENTER("load_driver");
    if (run_basic_system_command("BLOAD READ.TIME")) {

        /* Check for a missing NSC. */
        if (! is_nsc_absent()) {
            fprintf(stderr, "The No-Slot Clock hardware is missing");
            status = true;
        }
    }
    TRACE_RET_BOOL("load_driver", status);
    return status;
}

/**
 * The setup function must be called first.
 */
struct tm *read_time(struct tm *t)
{
    /* Reload the current time from the No-Slot Clock into memory. */
    read_time_from_nsc();

    /* Transfer loaded values into a standard C struct tm. */
    t->tm_sec   = nsc->sec;
    t->tm_min   = nsc->min;
    t->tm_hour  = nsc->hour;
    t->tm_mday  = nsc->day_of_month;
    t->tm_mon   = nsc->month - 1;
    t->tm_year  = nsc->year + 100;
    t->tm_wday  = nsc->day_of_week == 7 ? 0 : nsc->day_of_week;
    t->tm_yday  = 0;
    t->tm_isdst = 0;
    return t;
}


