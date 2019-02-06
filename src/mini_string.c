#include <mini_string.h>

#define CHAR_TO_NUMBER(chr)  (chr - '0')

size_t mini_strlen(const char * str)
{
    size_t len = 0;

    while(*str++)
    {
        len++;
    }

    return len;
}

int32_t mini_strcmp(const char * str1, const char * str2)
{
    while (*str1)
    {
        if (*str1 == *str2)
        {
            str1++;
            str2++;
        }
        else
        {
            break;
        }
    }

    return (*str1 - *str2);
}

int32_t mini_strncmp(const char * str1, const char * str2, size_t len)
{
    while (*str1)
    {
        if (*str1 == *str2 && len--)
        {
            str1++;
            str2++;
        }
        else
        {
            break;
        }
    }

    return (*str1 - *str2);
}

bool mini_strstartswith(const char * str, const char * prefix)
{
    while(*str)
    {
        if (*str == *prefix)
        {
            str++;
            prefix++;
        }
        else
        {
            break;
        }
    }

    return !(*prefix);
}

char * mini_strstr(const char * look_here, const char * for_this)
{
    do
    {
        if (mini_strstartswith(look_here, for_this))
        {
            return (char *)look_here;
        }
    } while(*look_here++);

    return NULL;
}

char * mini_strchr(const char * str, char chr)
{
    do
    {
        if (*str == chr)
        {
            return (char *)str;
        }
    } while (*str++);

    return NULL;
}

static inline bool is_digit(char chr)
{
    return (('0' <= chr) && (chr <= '9'));
}

static inline bool is_white(char chr)
{
    return (chr <= ' ');
}

int32_t mini_atoi(const char * str)
{
    int32_t val = 0;
    bool minus = false;

    char chr;
    while ((chr = *str++))
    {
        if (is_digit(chr))
        {
            val = val * 10 + CHAR_TO_NUMBER(chr);
        }
        else if (chr == '-')
        {
            minus = true;
        }
        else if (!is_white(chr) || val)
        {
            break;
        }
    }

    if (minus)
    {
        val = -val;
    }
    return val;
}


