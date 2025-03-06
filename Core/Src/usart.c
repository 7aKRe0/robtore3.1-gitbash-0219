/*
 * usart.c
 *
 *  Created on: Mar 5, 2025
 *      Author: uchuu
 */


#include "usart.h"

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart6, (uint8_t*) ptr, len, HAL_MAX_DELAY);
    return len;
}
