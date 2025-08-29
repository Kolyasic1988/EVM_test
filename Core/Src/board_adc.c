/*
 ====================================================================
 = Description:                  Фунции для работы с АЦП.
 = File name:                    board_adc.c 
====================================================================
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_var.h"
#include "board_def.h"
#include "adc.h"
#include "module_termistor.h"
#include "queue.h"

static QueueHandle_t xAdcQueue;

/***************************************************************************/
/**
 *  @brief  Инициализация задачи АЦП
 */
void vInitAdcTask(void)
{
    // Создаём очередь для adc_data_t
    xAdcQueue = xQueueCreate(ADC_QUEUE_LENGTH, ADC_QUEUE_ITEM_SIZE);
    configASSERT(xAdcQueue != NULL);

    xTaskCreateStatic(
        vAdcTask,                     // Функция таски
        "AdcTask",                    // Имя таски
        configMINIMAL_STACK_SIZE,     // Размер стека таски
        NULL,                         // Без аргументов
        osPriorityNormal,             // Приоритет - базово
        xAdcTaskStack,                // Массив стека
        &xAdcTaskTCB                  // Контрольный блок
    );
}


/***************************************************************************/
/**
 * @brief  Таска обработки данных с АЦП
 */
void vAdcTask(void *pvArg) {
    (void)(pvArg);
    //Запускаем АЦП в режиме непрерывного сканирования
    HAL_ADC_Start_IT(&hadc1);

    adc_data_t adc_data = { {0, 0}};
    for(;;) {
        // Ждём данные из очереди
        if (xQueueReceive(xAdcQueue, &adc_data, portMAX_DELAY) == pdPASS) {
          // Обработка данных с АЦП (вызов функции обработки термисторов)
          vCalculateTermistorTemp(&adc_data);
        }
    }
}

/***************************************************************************/
/**
  * @brief  Callback функция , вызывающаяся при окончании преобразования АЦП
  * @param  hadc: - указатель на дескриптор АЦП
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc == &hadc1) {
        adc_data_t adc_data = {{0, 0}};
        // Считываем два значения подряд (для двух каналов в последовательности)
        adc_data.buf[ADC_CH0] = HAL_ADC_GetValue(hadc); // Нулевой канал
        adc_data.buf[ADC_CH1] = HAL_ADC_GetValue(hadc); // Первй канал
        xQueueSendFromISR(xAdcQueue, &adc_data, NULL);
    }
}
/***************************************************************************/
/**
  * @brief Проверка допуска по значениям напряжения и токов каналов
  */
void vAdcCheckParameters(void) {
    // првоеряем полученные значения с АЦП
    // если они после расчетов выходят за допустимые пределы
    // выставляем флаги ошибок термисторов
    vCheckTermistorTemp();
}



