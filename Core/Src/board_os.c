/*
 ====================================================================
 = Description:                  Главная задача проекта
 = File name:                    board_os.c 
 ====================================================================
 */

#include "stm32f4xx_hal.h"
#include "board_func.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board_def.h"

/***************************************************************************/
//Основная таска обработки работы проекта
void vMainAppTask(void *pvArg)
{
  (void)(pvArg);
  //Дождаться когда подыментся CAN
  WAIT_CAN_UP();
  //Запускем преобразования АЦП
  vStartAdcTimer();
  for(;;) {
    vRunHandlers();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}