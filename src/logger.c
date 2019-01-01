#include <logger.h>
#include <ring_buffer.h>
#include <mini_printf.h>

#define LOG_PREFIX_LEN  (sizeof(LOG_PREFIX) - 1)

static char log_tx_buf[LOG_TX_BUFFER_SIZE + LOG_PREFIX_LEN] = LOG_PREFIX;

typedef struct
{
    const char * string;
    uint32_t     arg1;
    uint32_t     arg2;
    uint32_t     arg3;
    uint32_t     arg4;
} log_msg_t;

static log_msg_t log_msgs[LOG_ITEM_CAPACITY];
static ringbuf_t log_ringbuf;

static log_out_handler_t log_out;

void log_init(log_out_handler_t log_out_handler)
{
    log_out = log_out_handler;

    ringbuf_init(&log_ringbuf,
                 (void *)log_msgs,
                 sizeof(log_msg_t),
                 sizeof(log_msgs));
}

void log_msg(const char * string, ...)
{
    va_list va;
    va_start(va, string);

    log_msg_t log_msg;

    log_msg.string = string;
    log_msg.arg1 = va_arg(va, uint32_t);
    log_msg.arg2 = va_arg(va, uint32_t);
    log_msg.arg3 = va_arg(va, uint32_t);
    log_msg.arg4 = va_arg(va, uint32_t);

    ringbuf_put(&log_ringbuf, (void *)&log_msg);

    va_end(va);
}

void log_process(void)
{
    log_msg_t log_msg;
    uint32_t bytes_written;
    uint32_t bytes_left;
    uint32_t idx = 0;

    while (ringbuf_count_get(&log_ringbuf))
    {
        ringbuf_peek(&log_ringbuf, (void *)&log_msg);

        bytes_left = LOG_TX_BUFFER_SIZE - idx;
        bytes_written = mini_snprintf(&log_tx_buf[idx + LOG_PREFIX_LEN],
                                       bytes_left,
                                       log_msg.string,
                                       log_msg.arg1,
                                       log_msg.arg2,
                                       log_msg.arg3,
                                       log_msg.arg4);

        if (bytes_written < bytes_left)
        {
            idx += bytes_written;
            ringbuf_next(&log_ringbuf);
        }
        else
        {
            break;
        }
    }

    if (idx)
    {
        log_out(log_tx_buf, idx + LOG_PREFIX_LEN);
    }
}

