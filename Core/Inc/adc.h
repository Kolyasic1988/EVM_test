#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx_hal.h"

// Решил для простоты не измерять V REF, а задать константой
// Думаю в данном случае тоности хватит.
#define ADC_REF_VOLTAGE     (3.3)
#define ADC_MAX_VAL         (4095)

extern ADC_HandleTypeDef hadc1;

#endif /*__ADC_H */