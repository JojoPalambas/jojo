#ifndef INCLUDE_H
#define INCLUDE_H

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#define PAGE_SIZE page_size()

/* Structure used to store the first data blocks pointers */
struct global
{
    uint32_t nb_pages;
    void *meta;
};

/* Function that returns the size of a page */
unsigned page_size();

/* Function that moves any pointer n bytes */
void *move(void *ptr, int n);

/* Returns 2 to the power n */
size_t pow2(char n);

/* Function that returns the difference in bytes between two vectors */
int diff(void *ptr1, void *ptr2);

/* Function asked by the subject */
void *malloc(size_t size);
void *calloc(size_t number, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

#endif
