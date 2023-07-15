//
// Created by 11 on 2023/7/3.
//

#include <malloc.h>
#include <sys/unistd.h>

#include "mmu.h"
#include "ucos_ii.h"

vpage_t pageTbls[OS_LOWEST_PRIO + 1][PG_TBL_SIZE];

physical_memory_t *pagePool;

//void* vmalloc(unsigned int size) {
//    page_table_t task_pgTbl = pageTbls[OSPrioCur];
//    // 为用户分配一段虚拟地址，并把虚拟地址范围内的物理页面分配好
//    if (task_pgTbl.allocRecord.occupied_size + size > PG_TBL_SIZE * PG_SIZE) {
//        return NULL;
//    }
//    alloc_record_t *record = malloc(sizeof(alloc_record_t));
//    // 连续分配，从后往前释放，才可以这样，需要优化成找空闲连续地址
//    record->vaddr = (void*) task_pgTbl.allocRecord.occupied_size;   // 改成空闲块的起始地址
//    task_pgTbl.allocRecord.occupied_size += size;
//    record->size = size;
//    record->pre = task_pgTbl.allocRecord.head;
//    record->next = task_pgTbl.allocRecord.head->next;
//    task_pgTbl.allocRecord.head->next->pre = record;
//    task_pgTbl.allocRecord.head->next = record;
//
//    if (task_page_tbl->item_index >= PG_TBL_SIZE) {
//        return NULL;
//    }
//    // 获取上一个分配的页的虚拟尾地址
//    unsigned int ppg_no = task_page_tbl->table[task_page_tbl->item_index - 1];
//    ppage_t *ppg = pagePool->start_addr + ppg_no;
//    unsigned int last_pg_offset = (unsigned int) ppg->occupied_end & PG_OFFSET_MASK;
//    if (pagePool->freelist == NULL) {
//        // todo 扩容
//        return NULL;
//    }
//    // 从空闲链表中取出一个页
//    ppage_t *new_pg = pagePool->freelist;
//    pagePool->freelist = new_pg->next;
//    // todo 记录初始虚拟地址，一个虚页号对应多个物理页号
//    // 第一个页要从上次分配虚拟地址结束位置开始
//    new_pg->occupied_start = new_pg->page_start + (last_pg_offset / ALLOCATION_UNIT);
//    if (new_pg->occupied_start + (size / ALLOCATION_UNIT) < new_pg->page_start + (PG_SIZE / ALLOCATION_UNIT)) {
//        // 一个页足够
//        new_pg->occupied_end = new_pg->occupied_start + (size / ALLOCATION_UNIT);
//        task_page_tbl->table[task_page_tbl->item_index++] = (unsigned int) new_pg->page_start >> ADDRESS_SHIFT;
//        return (void *) (((task_page_tbl->item_index - 1) << ADDRESS_SHIFT) + last_pg_offset);
//    } else {
//        // 一个页不够
//        size -= (new_pg->page_start + (PG_SIZE / ALLOCATION_UNIT) - new_pg->occupied_start) * ALLOCATION_UNIT;
//        new_pg->occupied_end = new_pg->page_start + (PG_SIZE / ALLOCATION_UNIT);
//    }
//    while (size >= PG_SIZE) {
//        // 分配整页
//        if (pagePool->freelist == NULL) {
//            // 扩容
//            return NULL;
//        }
//        ppg = pagePool->freelist;
//        pagePool->freelist = ppg->next;
//        ppg->occupied_start = ppg->page_start;
//        ppg->occupied_end = ppg->page_start + (PG_SIZE / ALLOCATION_UNIT);
//        task_page_tbl->table[task_page_tbl->item_index++] = (unsigned int) ppg->page_start >> ADDRESS_SHIFT;
//        size -= PG_SIZE;
//    }
//    if (size > 0) {
//        // 分配剩余部分
//        if (pagePool->freelist == NULL) {
//            // 扩容
//            return NULL;
//        }
//        ppg = pagePool->freelist;
//        pagePool->freelist = ppg->next;
//        ppg->occupied_start = ppg->page_start;
//        ppg->occupied_end = ppg->page_start + (size / ALLOCATION_UNIT);
//        task_page_tbl->table[task_page_tbl->item_index++] = (unsigned int) ppg->page_start >> ADDRESS_SHIFT;
//    }
//
//    return new_pg->occupied_start;
//}
//
//void vfree(void* vaddr) {
//    page_table_t *task_page_tbl = &pageTbl[OSPrioCur];
//    unsigned int vpg_no = (unsigned int) vaddr >> ADDRESS_SHIFT;
//}

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
    // todo 不需要malloc，直接指定一段sdram地址
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