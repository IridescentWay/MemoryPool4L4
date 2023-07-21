#include <string.h>
#include <malloc.h>
#include "ucos_ii.h"
#include "stm32l4xx_hal.h"
#include "LED.h"
#include "lz4.h"
#include "mmu.h"

void compressTest(void *p_arg) {
    void* vaddr = (void *) 0x0001;
    char* dataBase = "习近平指出今年是中阿建交65周年65年前反对帝国主义和殖民主义争取民族独立解放的共同事业使我们两国走到一65年来中国和阿尔及利亚始终患难与共守望相助相互理解相互支持是追求共同发展和民族振兴道路上的真诚朋友天然伙伴中方正在以中国式现代化全面推进中华民族伟大复兴阿方正在着力推进建设新阿尔及利亚中方愿同阿方一道努力发扬光大传统友谊推动中阿全面战略伙伴关系取得更大发展";
    int size = strlen(dataBase) + 1;
    char* data = malloc(2048u * 16);
    int idx = 0;
    for (; idx < (2048u * 16) / size; ++idx) {
        memcpy(data + idx * size, dataBase, strlen(dataBase));
    }
    data[idx * size] = '\0';
    vwrite(vaddr, data, strlen(data) + 1);
    char *buf = malloc(LZ4_COMPRESSBOUND(strlen(data) + 1));
    vread(vaddr, buf, strlen(data) + 1);
    printf("%s\n", buf);
}
