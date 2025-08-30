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
#include <stdint.h>
#include <stdbool.h>

static uint32_t ntc_error_flag[NTC_SENSOR_COUNT];

static bool isTempOk(float temp_buf);
static float fCalculateNTCTemperature(uint16_t adc_value);
/***************************************************************************/
/**
  * @brief Обработка температуры с термисторов
  * 
  */
float fProcessTermistor(uint16_t adc_value, NTCSensorNames_e sensor) {
    if (sensor >= NTC_SENSOR_COUNT) {
        return 0.0f;
    }
    float temp = fCalculateNTCTemperature(adc_value);
    ntc_error_flag[sensor] += isTempOk(temp) ? 0 : 1;
    return temp;
}

/***************************************************************************/
/**
  * @brief  Расчёт температуры по данным с термисторов
  *         (используется формула для термисторов NTC)
  *         По значению - тк до 32 бит данных разницы в перфомансе не будет
  *         Получаем доп безопасность
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
  * @brief  Проверка показаний термисторов
  */
static bool isTempOk(float temp_buf) {
    if (temp_buf < NTC_TEMP_MIN || temp_buf > NTC_TEMP_MAX) {
        return false;
    }
    return true;
}

/***************************************************************************/
/**
  * @brief  Получение количества ошибок по термистору
  */
uint32_t getErrorCount(NTCSensorNames_e sensor) {
    if (sensor >= NTC_SENSOR_COUNT) {
        return 0;
    }
    return ntc_error_flag[sensor];
}
  