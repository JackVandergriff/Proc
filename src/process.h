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
    int8_t current;         // Stores current output data
    int8_t buffers;         // Stores # of buffer pages
    int8_t current_buffer;  // Stores current buffer index to avoid looping
    int8_t input_mask;      // masks input, right-aligned       (ex. 0b00001111)
    int8_t output_mask;     // masks output, left of registers  (ex. 0b00111100)
    int8_t register_mask;   // masks registers, right-aligned   (ex. 0b00000011)
    int8_t register_roll;   // # to roll left to put registers above inputs (4 for above example)
} typedef Header;

struct page {               // Stores main lookup table entries, indexed by input #
    int8_t entries[8];
} typedef Page;

struct buffer_page {        // Stores output from batch processing to keep tables in cache longer
    int8_t entries[8];
} typedef BufferPage;

struct footer {             // Stores reference to next block being used
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