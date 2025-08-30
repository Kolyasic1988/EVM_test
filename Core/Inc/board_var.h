/*
 ====================================================================
 = Description:                  Глобальные переменные для проекта
 = File name:                    board_var.h
 ====================================================================
 */
#ifndef __BOARD_VAR_H
#define __BOARD_VAR_H

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_def.h"

extern StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xMainAppTaskTCB;

extern StackType_t xAdcTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xAdcTaskTCB;

extern QueueHandle_t xCanTempQueue;
extern StaticQueue_t xCanTempQueueStruct;
extern uint8_t xCanTempQueueStorage[CAN_TX_QUEUE_LENGTH * CAN_TX_QUEUE_ITEM_SIZE];
#endif /*__BOARD_VAR_H */