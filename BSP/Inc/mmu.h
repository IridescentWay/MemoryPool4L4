//
// Created by 11 on 2023/7/3.
//

#ifndef MEMORYPOOL4L4_MMU_H
#define MEMORYPOOL4L4_MMU_H

#include "os_cfg.h"

#define PG_SIZE 512u
#define PG_OFFSET_MASK 0x1ffu
#define ADDRESS_SHIFT 9u
#define PG_TBL_SIZE 512u
#define PG_POOL_SIZE 128u

typedef struct page {
    void* start_addr;
    unsigned int allocated: 1;
} page_t;

// 页表中存放物理页号，索引号(0 ~ PG_TBL_SIZE)就是虚拟页号
typedef struct page_table {
    unsigned int item_index;
    unsigned int table[PG_TBL_SIZE];
} page_table_t;

extern page_table_t pageTbl[OS_LOWEST_PRIO + 1];

typedef struct memory_pool {
    void* start_addr;
    page_t  *expansion_page;
    page_t *freelist;
    page_t page_pool[];
} memory_pool_t;

extern memory_pool_t *pagePool;

void *vmalloc(unsigned int size);
void vfree(void *ptr);
void memoryPoolInit();

#endif //MEMORYPOOL4L4_MMU_H
