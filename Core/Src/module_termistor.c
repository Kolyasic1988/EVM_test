/**
  * @file module_termistor.c
  * @brief Функции обработки данных с термисторов.
  *
  */
#include "module_termistor.h"
#include "module_func.h"

float temp_buf[ADC_CHANNELS_NUM];

static float fCalculateNTCTemperature(uint16_t adc_value) {
    float temperature = 0.0f;
    // TODO
    return temperature;
}
/***************************************************************************/
/**
  * @brief  Расчёт температуры по данным с термисторов
  *         (используется формула для термисторов NTC)
  */
void vCalculateTermistorTemp(adc_data_t *adc_data) {
  // получаем данные с adc_data.ch0 и adc_data.ch1
  // рассчитываем температуру по формуле
  // сохраняем результат в структуру
  temp_buf[ADC_CH0] = fCalculateNTCTemperature(adc_data->buf[ADC_CH0]);
  temp_buf[ADC_CH1] = fCalculateNTCTemperature(adc_data->buf[ADC_CH1]);
}


/***************************************************************************/
/**
  * @brief  Проверка показаний термисторов
  */
void vCheckTermistorTemp(void) {

}