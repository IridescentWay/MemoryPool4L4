//
// Created by 11 on 2023/7/3.
//

#ifndef MEMORYPOOL4L4_MMU_H
#define MEMORYPOOL4L4_MMU_H

#include "os_cfg.h"

#define PG_SIZE 4096u    // == 512B
#define PG_OFFSET_MASK 0x1ffu
#define ADDRESS_SHIFT 9u
#define PG_TBL_SIZE 512u
#define PG_POOL_SIZE 128u
#define ALLOCATION_UNIT 8u

typedef struct alloc_record {
    unsigned int size;
    void *vaddr;
    struct alloc_record *pre;
    struct alloc_record *next;
} alloc_record_t;

//typedef struct alloc_record_head {
//    unsigned int occupied_size;
//    alloc_record_t *head;
//} alloc_record_head_t;

typedef struct ppage {
    void* page_start;
    struct ppage *next;
} ppage_t;

typedef struct vpage {
    unsigned int allocated;
    unsigned int ppg_no;
} vpage_t;

typedef vpage_t* page_table_t;

//typedef struct page_table {
////    alloc_record_head_t allocRecord;
////    alloc_record_head_t freeRecord;
//    vpage_t table[PG_TBL_SIZE];
//} page_table_t;

// 页表中存放物理页号，索引号(0 ~ PG_TBL_SIZE)就是虚拟页号
extern vpage_t pageTbls[OS_LOWEST_PRIO + 1][PG_TBL_SIZE];

typedef struct physical_memory {
    void* offer_addr;
    ppage_t * start_addr;
    ppage_t *freelist;
} physical_memory_t;

extern physical_memory_t *pagePool;

void *vmalloc(unsigned int size);
void vfree(void *ptr);
void memoryPoolInit();

#endif //MEMORYPOOL4L4_MMU_H
