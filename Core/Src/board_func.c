/*
 ====================================================================
 = Description:                  Главный файл проекта с логикой
 = File name:                    board_func.c
 ====================================================================
 */
#include "stm32f4xx.h"
#include "board_func.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

/***************************************************************************/
/**
  * @brief Главный обработчик всего
  */
void vRunHandlers(void)
{
  //тут будет проверять что надо послать данные в CAN
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