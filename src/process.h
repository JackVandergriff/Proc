#ifdef __cplusplus
extern "C" {
#endif

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include "utility.h"

// #define DEBUG

struct header {
    int8_t current;
    int8_t buffers;
    int8_t current_buffer;
    int8_t input_mask;
    int8_t output_mask;
    int8_t register_mask;
    int8_t register_roll;
} typedef Header;

struct page {
    int8_t entries[8];
} typedef Page;

struct buffer_page {
    int8_t entries[8];
} typedef BufferPage;

struct footer {
    union sector* ref;
    int8_t pad[8 - sizeof(void*)/sizeof(int8_t)];
} typedef Footer;

union sector {
    Header header;
    Page page;
    Footer footer;
    BufferPage buffer_page;
} typedef Sector;

char getRoll(int8_t);
Sector* createBlock(int8_t, int8_t, int8_t, int8_t);
void makeEntry(Sector*, int8_t, int8_t);
int8_t __always_inline lookup(Sector*, int8_t);

#endif

#ifdef __cplusplus
}
#endif