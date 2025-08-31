/*
 ====================================================================
 = Description:                  Главный файл проекта с логикой
 = File name:                    board_func.c
 ====================================================================
 */
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_def.h"
#include "board_var.h"
#include "ntc_termistor_def.h"

static QueueTemp_t sensorTemp;

/***************************************************************************/
/**
 *  @brief  Инициализация xState
 * @brief  Установка кода ошибки
 */
void vInitxState(void) {
    taskENTER_CRITICAL();
    xState.ulUptime = HAL_GetTick();
    xState.eDevError = ERROR_NONE;
    xState.fTemp[NTC_SENS1] = 0.0f;
    xState.fTemp[NTC_SENS2] = 0.0f;
    taskEXIT_CRITICAL();
}

/***************************************************************************/
/**
  * @brief  Формирует CAN пакет по пользовательским данным
  * 
  */

// Функция отправки двух float по CAN
static void vSendDataToCan(CAN_HandleTypeDef *hcan, uint8_t type, const void *data, uint8_t data_len) {
    
    CanDataFrame_t txData = {0};
    // Первый байт — адрес, далее пользовательские данные (до 7 байт)
    txData.addr = SELF_CAN_ADDRESS;
    txData.ucCode = type;
    if (data_len > 6) data_len = 6;
    memcpy(&txData.ucData[0], data, data_len);

    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    txHeader.StdId = SELF_CAN_ADDRESS;
    txHeader.ExtId = 0;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = data_len + 1; // адрес + данные
    txHeader.TransmitGlobalTime = DISABLE;

    HAL_StatusTypeDef status = HAL_CAN_AddTxMessage(hcan, &txHeader, (uint8_t*)&txData, &txMailbox);
        if (status != HAL_OK) {
            taskENTER_CRITICAL();
            xState.eDevError = ERROR_CAN;
            taskEXIT_CRITICAL();
            return;
        }
}

/***************************************************************************/
/**
  * @brief Главный обработчик всего
  */
void vRunHandlers(void)
{
    if (xQueueReceive(xCanTempQueue, &sensorTemp, portMAX_DELAY) == pdPASS) {
        vSendDataToCan(&hcan1, sensorTemp.type, 
                        (const void*) &sensorTemp.temp, sizeof(sensorTemp.temp));
    }
}


/***************************************************************************/
/**
  * @brief  FreeRTOS Idle Hook: MCU sleep в простое
  */
void vApplicationIdleHook(void)
{
#if (configUSE_IDLE_HOOK == 1)
    __WFI();
#endif
}

/***************************************************************************/
/**
 *  @brief  Инициализация очереди CAN
 */
void vInitCanQueue(void)
{
    xCanTempQueue = xQueueCreateStatic(
        CAN_TX_QUEUE_LENGTH,
        CAN_TX_QUEUE_ITEM_SIZE,
        xCanTempQueueStorage,
        &xCanTempQueueStruct
    );
    configASSERT(xCanTempQueue != NULL);
}
