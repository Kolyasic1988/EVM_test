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
#include <string.h>
#include <stdint.h>
/*======================ADC===========================*/

// очередь для данных АЦП
#define ADC_QUEUE_LENGTH        (10u)
#define ADC_QUEUE_ITEM_SIZE     (sizeof(AdcData_t))

//таймер для запуска преобразования АЦП
#define ADC_TIMER_PERIOD_TICKS  (pdMS_TO_TICKS(100u)) // 100 мс - 10Гц

/*======================CAN===========================*/

// Адрес устройства на шине CAN
#define SELF_CAN_ADDRESS          (42u)
#define CAN_FRAME_MAX_DATA_LENGTH (6u)
// Макрос для ожидания поднятия CAN
#define WAIT_CAN_UP() \
    do { \
        vTaskDelay(pdMS_TO_TICKS(1)); /* Просто ждем */ \
    } while((HAL_CAN_GetState(&hcan1) != HAL_CAN_STATE_READY));

// Структура простого CAN-фрейма с данными термисторов
typedef struct {
    uint8_t addr;
    uint8_t ucCode;
    int8_t ucData[CAN_FRAME_MAX_DATA_LENGTH];
} CanDataFrame_t;

_Static_assert(sizeof(CanDataFrame_t) == 8, "CanDataFrame_t must be 8 bytes");

// Типы сообщений по CAN
#define MSG_TYPE_NTC_SENSOR_1    (0xAA)
#define MSG_TYPE_NTC_SENSOR_2    (0xBB)

// Очередь для передачи данных в CAN
#define CAN_TX_QUEUE_LENGTH     (10u)
#define CAN_TX_QUEUE_ITEM_SIZE  (sizeof(QueueTemp_t))

//структура для очереди CAN
typedef struct {
    uint8_t type;
    float temp;
} QueueTemp_t;

#endif /*__BOARD_DEF_H */
