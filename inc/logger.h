#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdarg.h>
#include <stdint.h>

#define LOG_ITEM_CAPACITY  16

#define LOG_TX_BUFFER_SIZE  128

#define LOG_PREFIX  ""

typedef void (*log_out_handler_t)(char * buf, uint32_t len);

void log_init(log_out_handler_t log_out_handler);

void log_msg(const char * string, ...);

void log_process(void);

#endif // _LOGGER_H_
