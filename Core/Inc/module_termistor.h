/*
 ====================================================================
 = Description:                  Прототипы функций для работы с термисторами
 = File name:                    module_termistor.h
 ====================================================================
 */
#ifndef __module_termistor_H
#define __module_termistor_H

#include <stdint.h>

typedef enum {
  ADC_CH0 = 0,
  ADC_CH1 = 1,
  ADC_CHANNELS_NUM = 2
} ADC2ChNames_e;

typedef struct {
  uint16_t buf[ADC_CHANNELS_NUM];
} adc_data_t;

extern float temp_buf[ADC_CHANNELS_NUM];

extern void vCalculateTermistorTemp(adc_data_t *adc_data);
extern void vCheckTermistorTemp(void);

#endif /*__ __module_termistor_H */