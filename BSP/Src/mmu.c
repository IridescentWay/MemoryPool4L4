//
// Created by 11 on 2023/7/3.
//

#include <malloc.h>

#include "mmu.h"
#include "ucos_ii.h"

page_table_t pageTbl[OS_LOWEST_PRIO + 1];

memory_pool_t *pagePool;

void* vmalloc(unsigned int size) {

}

void vfree(void* vaddr) {

}

int vread(void* vaddr, void* buf, unsigned int size) {
    // 读出压缩过的内容
    // 解压缩恢复出来
    // 返回
}
// size = 125B
int vwrite(void* vaddr, void* buf, unsigned int size) {
    // 压缩



    // 写入

}

static void initMemoryPool(memory_pool_t **pool, unsigned int block_size, unsigned int block_num) {

}

void memoryPoolInit() {


}

static void freeMemoryPool(memory_pool_t *pool) {

}

void memoryPoolDeInit() {

}