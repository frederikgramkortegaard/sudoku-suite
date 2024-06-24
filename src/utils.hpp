
#pragma once
#include <string>
char *format_string(const char *format, ...);

#ifdef DEBUG
#define debug(str, args...) \
    printf("%s:%d:\t%s():\t" str, __FILE__, __LINE__, __func__, ##args)
#else
#define debug(str, args...) ;
#endif

#define err(str, args...)                                                        \
    fprintf(stderr, "[ERROR]:%s:%d:\t%s():\t" str, __FILE__, __LINE__, __func__, \
            ##args);                                                             \
    exit(-1)
