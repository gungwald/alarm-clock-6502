
void add_one_second(clock *clock)
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


/**
 * Doesn't work for all cases, but is not needed right now.
 */
void add_seconds(clock *clock, uint8_t seconds)
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

void old_print(clock *clock)
{
    printf("%2u:%02u:%02u %2s", clock->hours, clock->minutes, clock->seconds, convert_24_hour_to_meridiem(clock->hours));
}

void add_one_second(struct tm *t)
{
    if (t->tm_sec < 59) {
        ++(t->tm_sec);
    }
    else {
        t->tm_sec = 0;
        if (t->tm_min < 59) {
            ++(t->tm_min);
        }
        else {
            t->tm_min = 0;
            if (t->tm_hour < 23) {
                ++(t->tm_hour);
            }
            else {
                t->tm_hour = 0;
            }
        }
    }
}

