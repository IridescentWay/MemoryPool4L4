#include "ucos_ii.h"
#include "stm32l4xx_hal.h"
#include "LED.h"

void task_led_R_blink(void *p_arg) {
    while (1) {
        HAL_GPIO_TogglePin(LED_PIN_TYPE, LED_G);
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}
