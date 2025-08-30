/*
 ====================================================================
 = Description:                  Главная задача проекта
 = File name:                    board_os.c 
 ====================================================================
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_def.h"
/***************************************************************************/
//Основная таска обработки работы проекта
void vMainAppTask(void *pvArg)
{
    (void)(pvArg);
    //Дождаться когда подыментся CAN
    WAIT_CAN_UP();
    vInitCanQueue();
    vStartAdcTimer();
    for(;;) {
        vRunHandlers();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}