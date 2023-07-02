#include "stm32l4xx_hal.h"
#include "LED.h"

void LED_Init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    HAL_GPIO_WritePin(LED_PIN_TYPE,LED_R,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_TYPE,LED_G,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PIN_TYPE,LED_B,GPIO_PIN_SET);

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = LED_R;
    HAL_GPIO_Init(LED_PIN_TYPE,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED_G;
    HAL_GPIO_Init(LED_PIN_TYPE,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED_B;
    HAL_GPIO_Init(LED_PIN_TYPE,&GPIO_InitStruct);
}
