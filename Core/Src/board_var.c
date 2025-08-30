/*
 ====================================================================
 = Description:                  Глобальные данные для проекта
 = File name:                    board_var.c
 ====================================================================
 */
#include "board_var.h"

// --- Статические ресурсы для главное задачи ---
StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xMainAppTaskTCB;

// --- Статические ресурсы для задачи АЦП ---
StackType_t xAdcTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xAdcTaskTCB;

// --- Очередь для передачи данных в CAN и её статические ресурсы ---
QueueHandle_t xCanTempQueue;
StaticQueue_t xCanTempQueueStruct;
uint8_t xCanTempQueueStorage[CAN_TX_QUEUE_LENGTH * CAN_TX_QUEUE_ITEM_SIZE];
