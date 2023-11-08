#ifndef OS_HOMEWORK_CONF_H
#define OS_HOMEWORK_CONF_H


typedef struct PTE{
    bool valid;
    int frame;
    bool dirty;
    int referenced;
    unsigned int reference_count; // for nfu algorithm
    unsigned long long count; // for aging algorithm
} PTE;

#endif


