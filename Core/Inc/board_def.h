/*
 ====================================================================
 = Description:                  Константы и определения для проекта
 = File name:                    board_def.h
 ====================================================================
 */
#ifndef __BOARD_DEF_H
#define __BOARD_DEF_H

#include "adc.h"
#include "can.h"

// очередь для данных АЦП
#define ADC_QUEUE_LENGTH        (10u)
#define ADC_QUEUE_ITEM_SIZE     sizeof(adc_data_t)

//таймер для запуска преобразования АЦП
#define ADC_TIMER_PERIOD_TICKS (pdMS_TO_TICKS(100)) // 100 мс - 10Гц

// Макрос для ожидания поднятия CAN
#define WAIT_CAN_UP() \
    do { \
      vTaskDelay(pdMS_TO_TICKS(1)); /* Просто ждем */ \
    } while((HAL_CAN_GetState(&hcan1) != HAL_CAN_STATE_READY));
    
#endif /*__BOARD_DEF_H */
