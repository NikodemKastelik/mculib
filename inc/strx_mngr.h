#ifndef _STRX_MNGR_H_
#define _STRX_MNGR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define STRX_MNGR_TERMINATING_CHAR  '\n'

typedef struct
{
    char *   buffer;
    size_t   total_size;
    uint32_t items_count;
    uint16_t wr_idx;
    uint16_t rd_idx;
} strx_mngr_t;

void strx_mngr_init(strx_mngr_t * strx_mngr,
                    char *        buffer,
                    uint16_t      total_size);

void strx_mngr_feed(strx_mngr_t * strx_mngr, char item);

bool strx_mngr_retrieve(strx_mngr_t * strx_mngr, char * string);

#endif // _LOGGER_H_
