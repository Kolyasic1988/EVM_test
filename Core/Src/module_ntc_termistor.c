/*
 ====================================================================
 = Description:                  Функции для работы с NTC термисторами
 = File name:                    module_ntc_termistor.c
 ====================================================================
 */
#include "module_ntc_termistor.h"
#include "board_func.h"
#include "adc.h"
#include <math.h>

float ntc_sensor_temp[NTC_SENSOR_COUNT];
int ntc_error_flag[NTC_SENSOR_COUNT];

/***************************************************************************/
/**
 * @brief  Внутренняя функция расчёта температуры по значению АЦП
 *        (используется формула для термисторов NTC)
 */
static float fCalculateNTCTemperature(uint16_t adc_value) {
    // Преобразование значения АЦП в напряжение
    float v_adc = ((float) adc_value / ADC_MAX_VAL) * ADC_REF_VOLTAGE;
    // Расчёт сопротивления термистора (NTC в нижнем плече делителя)
    float r_ntc = (DIVIDER_RESISTANCE * v_adc) / (VOLTAGE_SUPPLY - v_adc);
    // Расчёт температуры по B-формуле
    float temp_k = 1.0 / ((1.0 / (NTC_T0_KELVIN)) + (1.0 / NTC_B_COEFFICIENT) * logf(r_ntc / NTC_R0));
    return temp_k - 273.15;
}
/***************************************************************************/
/**
  * @brief  Расчёт температуры по данным с термисторов
  *         (используется формула для термисторов NTC)
  *         По значению - тк до 32 бит данных разницы в перфомансе не будет
  *         Получаем доп безопасность
  */
void vCalculateTermistorTemp(adc_data_t adc_data) {
  ntc_sensor_temp[0] = fCalculateNTCTemperature(adc_data.buf[NTC_SENSOR_1]);
  ntc_sensor_temp[1] = fCalculateNTCTemperature(adc_data.buf[NTC_SENSOR_2]);
  
  ntc_error_flag[0] = vCheckTermistorTemp(ntc_sensor_temp[0]);
  ntc_error_flag[1] = vCheckTermistorTemp(ntc_sensor_temp[1]);
  // теперь эти данные надо передать в CAN
  // Дано выставить флаг что данные готовы к отправке и парсить его в vMainAppTask на отправку данных
}

/***************************************************************************/
/**
  * @brief  Проверка показаний термисторов
  */
int vCheckTermistorTemp(float temp_buf) {
  if (temp_buf < NTC_TEMP_MIN || temp_buf > NTC_TEMP_MAX) {
    return -1;
  }
  return 0;
}
  