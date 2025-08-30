/*
 ====================================================================
 = Description:                  Прототипы функций для работы с NTC термисторами
 = File name:                    module_ntc_termistor.h
 ====================================================================
 */
#ifndef __MODULE_NTC_TERMISTOR_H
#define __MODULE_NTC_TERMISTOR_H

#include <stdint.h>

// --- NTC термистор параметры на основе таблицы ---
// { -40, 402000.0f },
// { -30, 200000.0f },
// { -20, 105000.0f },
// { -10, 58200.0f },
// {   0, 33660.0f },
// {  10, 20200.0f },
// {  20, 12500.0f },
// {  25, 10000.0f },
// {  30, 8040.0f },
// {  40, 5300.0f },
// {  50, 3590.0f },
// {  60, 2490.0f },
// {  70, 1760.0f },
// {  80, 1270.0f },
// {  90, 934.0f },
// { 100, 638.0f },
// { 110, 529.0f },
// { 150, 198.0f },
// { 200, 74.0f }

// По этиму параметры термистора расчитаны:
// На С++ - сделал бы расчеты в constexpr функции
#define NTC_B_COEFFICIENT   (3950.0)      // B (K)
#define NTC_R0              (10000.0)     // R0 (Ом) при T0
#define NTC_T0              (25.0)        // T0 (°C)
#define NTC_T0_KELVIN       (NTC_T0 + 273.15)

#define NTC_TEMP_MIN   (-40.0f)
#define NTC_TEMP_MAX   (125.0f)

// Параметры делителя напряжения для подключения термисторов
#define DIVIDER_RESISTANCE  (3300.0)
#define VOLTAGE_SUPPLY      (5.0)

typedef enum {
    NTC_SENSOR_1     = 0,
    NTC_SENSOR_2     = 1,
    NTC_SENSOR_COUNT = 2
} NTCSensorNames_e;

typedef struct {
    uint16_t buf[NTC_SENSOR_COUNT];
} AdcData_t;

// Массив для хранения текущих температур с термисторов

extern float fProcessTermistor(uint16_t adc_value, NTCSensorNames_e sensor);
extern uint32_t getErrorCount(NTCSensorNames_e sensor);
#endif /*__MODULE_NTC_TERMISTOR_H */