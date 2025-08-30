/*
 ====================================================================
 = Description:                  Фунции для работы с АЦП.
 = File name:                    board_adc.c 
====================================================================
 */

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "board_func.h"
#include "board_var.h"
#include "board_def.h"
#include "module_ntc_termistor.h"

static QueueHandle_t xAdcQueue;
static StaticQueue_t xAdcQueueStruct;
static uint8_t ucAdcQueueStorage[ADC_QUEUE_LENGTH * ADC_QUEUE_ITEM_SIZE];

static TimerHandle_t xAdcTimer;
static StaticTimer_t xAdcTimerStruct;

/***************************************************************************/
/**
 *  @brief  Callback функция таймера для запуска преобразования АЦП
 */
static void vAdcTimerCallback(void)
{
    HAL_ADC_Start_IT(&hadc1);
}

/***************************************************************************/
/**
 *  @brief  Запуск таймера для АЦП
 */
void vStartAdcTimer(void)
{
    if (xAdcTimer != NULL) { xTimerStart(xAdcTimer, 0); }
}

/***************************************************************************/
/**
 *  @brief  Инициализация таймера для АЦП
 */
static void vInitAdcTimer(void)
{
    xAdcTimer = xTimerCreateStatic(
        "AdcTmr",
        ADC_TIMER_PERIOD_TICKS,
        pdTRUE, // автоперезапуск
        NULL,
        (TimerCallbackFunction_t)vAdcTimerCallback,
        &xAdcTimerStruct
    );
    configASSERT(xAdcTimer != NULL);
    // Не стартуем таймер сразу
}

/***************************************************************************/
/**
 *  @brief  Инициализация очереди АЦП
 */
static void vInitAdcQueue(void)
{
    xAdcQueue = xQueueCreateStatic(
        ADC_QUEUE_LENGTH,
        ADC_QUEUE_ITEM_SIZE,
        ucAdcQueueStorage,
        &xAdcQueueStruct
    );
    configASSERT(xAdcQueue != NULL);
}

/***************************************************************************/
/**
 *  @brief  Инициализация задачи АЦП и примитивов синхронизации
 */
void vInitAdcTask(void)
{
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
    vInitAdcQueue();
    vInitAdcTimer();
    //Запускаем АЦП в режиме непрерывного сканирования
    HAL_ADC_Start_IT(&hadc1);
    AdcData_t adc_data = { {0, 0}};
    QueueTemp_t queue_temps[NTC_SENSOR_COUNT] = {{MSG_TYPE_NTC_SENSOR_1, 0.0},
                                                 {MSG_TYPE_NTC_SENSOR_2, 0.0}};
    for(;;) {
        // Ждём данные из очереди
        if (xQueueReceive(xAdcQueue, &adc_data, portMAX_DELAY) == pdPASS) {
            queue_temps[NTC_SENSOR_1].temp = fProcessTermistor(adc_data.buf[NTC_SENSOR_1], NTC_SENSOR_1);
            queue_temps[NTC_SENSOR_2].temp = fProcessTermistor(adc_data.buf[NTC_SENSOR_2],NTC_SENSOR_2);
            xQueueSend(xCanTempQueue, &queue_temps[NTC_SENSOR_1], portMAX_DELAY);
            xQueueSend(xCanTempQueue, &queue_temps[NTC_SENSOR_1], portMAX_DELAY);
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
        AdcData_t adc_data = {{0, 0}};
        // Считываем два значения подряд
        adc_data.buf[NTC_SENSOR_1] = HAL_ADC_GetValue(hadc);
        adc_data.buf[NTC_SENSOR_2] = HAL_ADC_GetValue(hadc);
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
}
