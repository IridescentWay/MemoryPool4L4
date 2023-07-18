//
// Created by 11 on 2023/7/3.
//

#include <malloc.h>
#include <sys/unistd.h>

#include "mmu.h"
#include "ucos_ii.h"

vpage_t pageTbls[OS_LOWEST_PRIO + 1][PG_TBL_SIZE];

physical_memory_t *pagePool;

size_t vread(void* vaddr, void* buf, size_t size) {
    unsigned int vpg_no = (unsigned int) vaddr >> ADDRESS_SHIFT;
    unsigned int pg_offset = (unsigned int) vaddr & PG_OFFSET_MASK;
    page_table_t task_page_tbl = (page_table_t) (page_table_t *) pageTbls[OSPrioCur];
    if (task_page_tbl[vpg_no].allocated == 0) {
        // 读未写入内容的地址返回-1
        return -1;
    }
    unsigned int ppg_no = task_page_tbl[vpg_no].ppg_no;
    void* paddr = (void *) ((ppg_no << ADDRESS_SHIFT) + pg_offset);
    // 读出压缩过的内容
    // 解压缩恢复出来
    // 返回
    return size;
}
// size = 125B
size_t vwrite(void* vaddr, void* buf, size_t size) {
    // 计算物理地址
    unsigned int vpg_no = (unsigned int) vaddr >> ADDRESS_SHIFT;
    unsigned int pg_offset = (unsigned int) vaddr & PG_OFFSET_MASK;
    page_table_t task_page_tbl = (page_table_t) pageTbls[OSPrioCur];
    if (task_page_tbl[vpg_no].allocated == 0) {
        task_page_tbl[vpg_no].ppg_no = (unsigned int)(pagePool->freelist->page_start) >> ADDRESS_SHIFT;
        pagePool->freelist = pagePool->freelist->next;
        task_page_tbl[vpg_no].allocated = 1;
    }
    unsigned int ppg_no = task_page_tbl[vpg_no].ppg_no;
    void* paddr = (void *) ((ppg_no << ADDRESS_SHIFT) + pg_offset);
    // 压缩

    // 写入
    return size;
}

void memoryPoolInit() {
    pagePool = (physical_memory_t*)malloc(sizeof(physical_memory_t));
    pagePool->offer_addr = malloc(PG_SIZE * (PG_POOL_SIZE + 1));
    void* start_addr = pagePool->offer_addr;
    while ((unsigned int)start_addr % PG_SIZE != 0) {
        start_addr++;
    }
    pagePool->start_addr = start_addr;
    pagePool->freelist = pagePool->start_addr;
    unsigned int ix;
    ppage_t *p1, *p2;
    for (ix = 0u; ix < PG_POOL_SIZE - 1; ++ix) {
        p1 = pagePool->start_addr + ix;
        p2 = pagePool->start_addr + ix + 1;
        p1->page_start = start_addr + ix * PG_SIZE;
        p1->next = p2;
    }
    p2->page_start = start_addr + ix * PG_SIZE;
    p2->next = NULL;
}

void memoryPoolDeInit() {

}