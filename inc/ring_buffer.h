#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    void *   buffer;
    size_t   total_size;
    uint16_t item_size;
    uint16_t wr_idx;
    uint16_t rd_idx;
    uint16_t items_count;
} ringbuf_t;

/**
 * @brief Function for initializing the ring buffer.
 *
 * Buffer provided by user must be big enough to hold
 * number of items of specified size.
 *
 * @param ringbuf     Pointer to ring buffer instance.
 * @param buffer      Buffer holding ring buffer items.
 * @param item_size   Size of one item in bytes.
 * @param total_size  Ring buffer size in bytes.
 */
void ringbuf_init(ringbuf_t * ringbuf,
                  void *      buffer,
                  uint16_t    item_size,
                  uint16_t    total_size);

void ringbuf_put(ringbuf_t * ringbuf, void * item);

void ringbuf_get(ringbuf_t * ringbuf, void * item);

void ringbuf_peek(ringbuf_t * ringbuf, void *item);

void ringbuf_next(ringbuf_t * ringbuf);

uint16_t ringbuf_count_get(ringbuf_t * ringbuf);

#endif // _RING_BUFFER_H_
