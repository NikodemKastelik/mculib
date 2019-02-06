#ifndef _MINI_STRING_H_
#define _MINI_STRING_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

size_t mini_strlen(const char * str);

int32_t mini_strcmp(const char * str1, const char * str2);

int32_t mini_strncmp(const char * str1, const char * str2, size_t len);

char * mini_strstr(const char * look_here, const char * for_this);

char * mini_strchr(const char * str, char chr);

bool mini_strstartswith(const char * str, const char * prefix);

int32_t mini_atoi(const char * str);

#endif // _MINI_STRING_H_
