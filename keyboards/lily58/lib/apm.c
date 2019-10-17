#include <stdio.h>
#include "lily58.h"

#define NUM_SECS 1
#define NUM_MS NUM_SECS * 1000
#define MS_BUCKET 10
#define NUM_BUCKETS NUM_MS / MS_BUCKET

char apm_str[24] = {};
unsigned int last_time = 0;

char time_buffer[NUM_BUCKETS] = {};
int apm_count = 0;

// because the % operator is wonky af and not working, use this instead
unsigned int mod(unsigned int a, unsigned int b)
{
    return a - (a / b) * b;
}

void record_apm_action(void) {
  unsigned int cur_time = timer_read();
  unsigned int cur_time_bucket = mod(cur_time / MS_BUCKET, NUM_BUCKETS);
  time_buffer[cur_time_bucket]++;
  apm_count++;
}

const char *read_apm(void) {
    unsigned int cur_time = timer_read();
    unsigned int last_time_bucket = mod(last_time / MS_BUCKET, NUM_BUCKETS);
    unsigned int cur_time_bucket = mod(cur_time / MS_BUCKET, NUM_BUCKETS);
    last_time = cur_time;

    // This assumes we can only jump one bucket at a time. Is this true?
    if (last_time_bucket != cur_time_bucket)
    {
        apm_count -= time_buffer[cur_time_bucket];
        time_buffer[cur_time_bucket] = 0;
        if (apm_count < 0)
        {
            apm_count = 0;
        }
    }
    unsigned int apm_main = (apm_count * 60 / NUM_SECS);
    snprintf(apm_str, sizeof(apm_str), "%d APM", apm_main);
    return apm_str;
}
