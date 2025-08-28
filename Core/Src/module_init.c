/**
  * @file module_init.c
  * @brief ФУнкции инициализации периферии и задач проекта.
  *
  */

#include "module_func.h"
#include "module_var.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
/********************************************************************/
/**
  * @brief  Стартовая инициализация периферии и задач проекта.
  */

 void Init_MainAppTask(void)
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
    Init_MainAppTask();
}

