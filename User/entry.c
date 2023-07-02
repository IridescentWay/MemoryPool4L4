#include "stm32l4xx_hal.h"
#include "os_cfg.h"
#include "LED.h"
#include "tasks.h"
#include "ucos_ii.h"

static OS_STK task_led_R_stk[128];

void SysTick_init(void)
{
    SysTick_Config(HAL_RCC_GetSysClockFreq() / OS_TICKS_PER_SEC);
}

void user_entry() {
    SysTick_init();
    LED_Init();
    OSInit();
    OSTaskCreate(task_led_R_blink, (void *) 0, &task_led_R_stk[127], 6);
    OSStart();
}