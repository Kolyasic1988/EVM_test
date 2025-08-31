/*
 ====================================================================
 = Description:                  Прототипы функций для работы с NTC термисторами
 = File name:                    module_ntc_termistor_func.h
 ====================================================================
 */
#ifndef __MODULE_NTC_TERMISTOR_FUNC_H
#define __MODULE_NTC_TERMISTOR_FUNC_H

#include <stdint.h>
#include "ntc_termistor_def.h"

extern void ntc_termistor_init(float ref_voltage, uint16_t max_val);

extern float fProcessTermistor(uint16_t adc_value, NTCSensorNames_e sensor);
extern uint32_t ucNtcErrorCount(NTCSensorNames_e sensor);

#endif /*__MODULE_NTC_TERMISTOR_FUNC_H */