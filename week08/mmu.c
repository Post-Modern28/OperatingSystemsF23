#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define PAGES 100
#define FRAMES 20
#define PAGE_SIZE 8
#define PAGE_TABLE_SIZE (PAGES * sizeof(struct PTE))

struct PTE{
    bool valid;
    int frame;
    bool dirty;
    int referenced;
};

char disk[PAGES][PAGE_SIZE];
char RAM[FRAMES][PAGE_SIZE];
struct PTE *page_table;

void handle_signal(int sig) {
    int page_num = sig - SIGUSR1;
    struct PTE *pte = &page_table[page_num];
    if (!pte->valid) {
        int i;
        for (i = 0; i < FRAMES; i++) {
            if (page_table[i].valid && page_table[i].frame == pte->frame) {
                if (page_table[i].dirty) {
                    memcpy(&disk[pte->frame], &RAM[i], PAGE_SIZE);
                    printf("Page %d written to disk\n", i);
                }
                page_table[i].valid = false;
                page_table[i].frame = -1;
                break;
            }
        }
        memcpy(&RAM[i], &disk[page_num], PAGE_SIZE);
        printf("Page %d loaded into frame %d\n", page_num, i);
        pte->valid = true;
        pte->frame = i;
        pte->dirty = false;
    } else {
        pte->referenced = 1;
    }
}

int main() {
    int i, fd;
    srand(228);
    for (i = 0; i < PAGES; i++) {
        sprintf(disk[i], "Page %02d", i);
    }
    fd = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ftruncate(fd, PAGE_TABLE_SIZE);
    page_table = mmap(NULL, PAGE_TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    for (i = 0; i < PAGES; i++) {
        page_table[i].valid = false;
        page_table[i].frame = -1;
        page_table[i].dirty = false;
        page_table[i].referenced = 0;
    }
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);
    while (true) {
        pause();
    }
}

