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

#define GETINPUTLEN(x)     ((x) & 0b1111)
#define GETOUTPUTLEN(x)    (((x) >> 4) & 0b1111)
#define GETOUTPUTROLL(x)   (((x) >> 12)& 0b1111)
#define GETREGISTERLEN(x)  (((x) >> 16)& 0b1111)
#define GETREGISTERROLL(x) (((x) >> 20)& 0b1111)

struct header {
    int8_t pages;
    int16_t current;
    int8_t buffers;
    int8_t current_buffer;
    // int8_t pad[5];
} typedef Header;

struct page {
    int16_t entries[4];
} typedef Page;

struct buffer_page {
    int16_t entries[4];
} typedef BufferPage;

struct footer {
    void* ref;
    int8_t pad[8 - sizeof(void*)/sizeof(int8_t)];
} typedef Footer;

union sector {
    Header header;
    Page page;
    Footer footer;
    BufferPage buffer_page;
} typedef Sector;

struct pageref {
    long IOR_map;
    int pages;
    int max_pages;
    Page current;
    Sector* ref;
} typedef Pageref;

int16_t makeEntry(Pageref*, int16_t);
Pageref createPageref(long, int);

#endif

#ifdef __cplusplus
}
#endif