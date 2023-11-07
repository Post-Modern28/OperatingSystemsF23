#ifndef OS_HOMEWORK_CONF_H
#define OS_HOMEWORK_CONF_H


typedef struct PTE{
    bool valid;
    int frame;
    bool dirty;
    int referenced;
} PTE;

#endif


