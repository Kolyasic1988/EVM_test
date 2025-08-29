/*
 ====================================================================
 = Description:                  Функции инициализации модулей
 = File name:                    board_init.c
 ====================================================================
 */

#include "board_func.h"
#include "board_var.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

/********************************************************************/
/**
  * @brief  Инициализация главной задачи
  */

 void vInitMainAppTask(void)
{
    xTaskCreateStatic(
        vMainAppTask,                 // Функция таски
        "MainApp",                    // Имя таски
        configMINIMAL_STACK_SIZE,     // Размер стека таски
        NULL,                         // Без аргументов
        osPriorityNormal,             // Приоритет - базово
        xMainAppTaskStack,            // Массив стека
        &xMainAppTaskTCB              // Контрольный блок
    );
}

void vInitUser(void)
{
    //Может инициализировать какие структуры данных?

}

void vInitUserTasks(void)
{
    vInitMainAppTask();
    vInitAdcTask();
}

