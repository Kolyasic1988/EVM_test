/*
 ====================================================================
 = Description:                  Функции для работы с NTC термисторами
 = File name:                    ntc_termistor.c
 ====================================================================
 */
#include "ntc_termistor_func.h"
#include "ntc_termistor_def.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

/***************************************************************************/
/**
  * @brief  Структура с параметрами по умолчанию для инициализации
  */
static NtcThermostor_t ntc_sensor = {
    .adc = {
        .ref_voltage = 3.3,
        .max_val = 4095
    },
    .params = {
        .b_coefficient = NTC_B_COEFFICIENT,
        .r0 = NTC_R0,
        .t0_kelvin = NTC_T0_KELVIN,
        .temp_min = NTC_TEMP_MIN,
        .temp_max = NTC_TEMP_MAX,
        .divider_resistance = DIVIDER_RESISTANCE,
        .voltage_supply = VOLTAGE_SUPPLY
    },
    .error_count = {0, 0}
};

static bool isTempOk(float temp_buf);
static float fCalculateNTCTemperature(uint16_t adc_value);

/***************************************************************************/
/**
  * @brief Обработка температуры с термисторов
  * 
  */
float fProcessTermistor(uint16_t adc_value, NTCSensorNames_e sensor) {
    if (sensor >= NTC_SENS_COUNT) {
        return 0.0f;
    }
    float temp = fCalculateNTCTemperature(adc_value);
    ntc_sensor.error_count[sensor] += isTempOk(temp) ? 0 : 1;
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
    float v_adc = ((float) adc_value / ntc_sensor.adc.ref_voltage) * ntc_sensor.adc.max_val;
    // Расчёт сопротивления термистора (NTC в нижнем плече делителя)
    float r_ntc = (ntc_sensor.params.divider_resistance * v_adc) / (ntc_sensor.params.voltage_supply - v_adc);
    // Расчёт температуры по B-формуле
    float temp_k = 1.0 / ((1.0 / (ntc_sensor.params.t0_kelvin)) + (1.0 / ntc_sensor.params.b_coefficient) * logf(r_ntc / ntc_sensor.params.r0));
    return temp_k - 273.15;
}

/***************************************************************************/
/**
  * @brief  Проверка показаний термисторов
  */
static bool isTempOk(float temp_buf) {
    if (temp_buf < ntc_sensor.params.temp_min || temp_buf > ntc_sensor.params.temp_max) {
        return false;
    }
    return true;
}

/***************************************************************************/
/**
  * @brief  Получение количества ошибок по термистору
  */
uint32_t ucNtcErrorCount(NTCSensorNames_e sensor) {
    if (sensor >= NTC_SENS_COUNT) {
        return 0;
    }
    return ntc_sensor.error_count[sensor];
}

/***************************************************************************/
/**
  * @brief  Инициализация модуля - получение параметров АЦП
  */
void vNtcTermistorInit(float ref_voltage, uint16_t max_val) {
    ntc_sensor.adc.ref_voltage = ref_voltage;
    ntc_sensor.adc.max_val = max_val;
}
