/*
 ====================================================================
 = Description:                  Функции инициализации модулей
 = File name:                    board_init.c
 ====================================================================
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_var.h"

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
    //xState какая нибудь
}

void vInitUserTasks(void)
{
    vInitMainAppTask();
    vInitAdcTask();
}
