#include <ring_buffer.h>

static void copy_item(void * from, void * to, size_t item_size)
{
    uint8_t * src_ptr = (uint8_t *)from;
    uint8_t * dst_ptr = (uint8_t *)to;
    while (item_size--)
    {
        *dst_ptr++ = *src_ptr++;
    }
}

void ringbuf_init(ringbuf_t * ringbuf,
                  void *      buffer,
                  uint16_t    item_size,
                  uint16_t    total_size)
{
    ringbuf->buffer = buffer;
    ringbuf->total_size = total_size;
    ringbuf->item_size = item_size;
    ringbuf->wr_idx = 0;
    ringbuf->rd_idx = 0;
    ringbuf->items_count = 0;
}

void ringbuf_put(ringbuf_t * ringbuf, void * item)
{
    void * from = item;
    void * to   = (void *)&((uint8_t *)ringbuf->buffer)[ringbuf->wr_idx];

    copy_item(from, to, ringbuf->item_size);

    ringbuf->wr_idx += ringbuf->item_size;
    if (ringbuf->wr_idx == ringbuf->total_size)
    {
        ringbuf->wr_idx = 0;
    }
    ringbuf->items_count++;
}

void ringbuf_peek(ringbuf_t * ringbuf, void *item)
{
    void * from = (void *)&((uint8_t *)ringbuf->buffer)[ringbuf->rd_idx];
    void * to   = item;

    copy_item(from, to, ringbuf->item_size);
}

void ringbuf_next(ringbuf_t * ringbuf)
{
    ringbuf->rd_idx += ringbuf->item_size;
    if (ringbuf->rd_idx == ringbuf->total_size)
    {
        ringbuf->rd_idx = 0;
    }
    ringbuf->items_count--;
}

void ringbuf_get(ringbuf_t * ringbuf, void * item)
{
    ringbuf_peek(ringbuf, item);
    ringbuf_next(ringbuf);
}

uint16_t ringbuf_count_get(ringbuf_t * ringbuf)
{
    return ringbuf->items_count;
}

