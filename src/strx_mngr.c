#include <strx_mngr.h>

void strx_mngr_init(strx_mngr_t * strx_mngr,
                    char *        buffer,
                    uint16_t      total_size)
{
    strx_mngr->buffer = buffer;
    strx_mngr->total_size = total_size;
    strx_mngr->wr_idx = 0;
    strx_mngr->rd_idx = 0;
    strx_mngr->items_count = 0;
}

void strx_mngr_feed(strx_mngr_t * strx_mngr, char item)
{
    if (item == '\0')
    {
        return;
    }

    if (item == STRX_MNGR_TERMINATING_CHAR)
    {
        strx_mngr->buffer[strx_mngr->wr_idx] = '\0';
        strx_mngr->items_count++;
    }
    else
    {
        strx_mngr->buffer[strx_mngr->wr_idx] = item;
    }

    strx_mngr->wr_idx++;
    if (strx_mngr->wr_idx == strx_mngr->total_size)
    {
        strx_mngr->wr_idx = 0;
    }
}

bool strx_mngr_retrieve(strx_mngr_t * strx_mngr, char * string)
{
    if (strx_mngr->items_count == 0)
    {
        return false;
    }

    char chr;
    do
    {
        chr = strx_mngr->buffer[strx_mngr->rd_idx++];
        *string++ = chr;

        if (strx_mngr->rd_idx == strx_mngr->total_size)
        {
            strx_mngr->rd_idx = 0;
        }
    } while (chr != '\0');

    strx_mngr->items_count--;

    return true;
}

