//
// Created by 11 on 2023/7/3.
//

#ifndef MEMORYPOOL4L4_MMU_H
#define MEMORYPOOL4L4_MMU_H

#include "os_cfg.h"

#define PG_SIZE 4096u    // == 4KB
#define PG_OFFSET_MASK 0x1ffu
#define ADDRESS_SHIFT 9u
#define PG_TBL_SIZE 64u
#define PG_POOL_SIZE 64u

typedef struct ppage {
    void* page_start;
    struct ppage *next;
} ppage_t;

typedef struct vpage {
    unsigned int allocated;
    unsigned int ppg_no;
} vpage_t;

typedef vpage_t* page_table_t;

// 页表中存放物理页号，索引号(0 ~ PG_TBL_SIZE)就是虚拟页号
extern vpage_t pageTbls[OS_LOWEST_PRIO + 1][PG_TBL_SIZE];

typedef struct physical_memory {
    void* offer_addr;
    ppage_t * start_addr;
    ppage_t *freelist;
} physical_memory_t;

extern physical_memory_t *pagePool;
size_t vread(void* vaddr, void* buf, size_t size);
size_t vwrite(void* vaddr, void* buf, size_t size);
void memoryPoolInit();

#endif //MEMORYPOOL4L4_MMU_H
