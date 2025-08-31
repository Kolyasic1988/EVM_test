/*
 ====================================================================
 = Description:                  Функции инициализации модулей и задач
 = File name:                    board_init.c
 ====================================================================
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_var.h"
#include "ntc_termistor_func.h"

/********************************************************************/
/**
  * @brief  Пользовательская инициализация
  */
void vInitUser(void)
{
    ntc_termistor_init(ADC_REF_VOLTAGE, ADC_MAX_VAL);
    // Может инициализировать какие структуры данных?
    // xState какая нибудь
}

/********************************************************************/
/**
  * @brief  Инициализация задач пользователя
  */
void vInitUserTasks(void)
{
    vInitMainAppTask();
    vInitAdcTask();
}

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
