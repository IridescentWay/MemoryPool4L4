#include "stm32l4xx_hal.h"
#include "os_cfg.h"
#include "LED.h"
#include "tasks.h"
#include "ucos_ii.h"
#include "usart.h"

static OS_STK task_led_R_stk[256];

void SysTick_init(void)
{
    SysTick_Config(HAL_RCC_GetSysClockFreq() / OS_TICKS_PER_SEC);
}

void user_entry() {
    SysTick_init();
    LED_Init();
    DEBUG_USART_CONFIG_INIT();
    OSInit();
    OSTaskCreate(task_led_R_blink, (void *) 0, &task_led_R_stk[255], 6);
    OSStart();
}