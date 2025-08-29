/**
  * @file module_var.h
  * @brief Константы и переменные для проекта.
  *
  */
#ifndef __module_var_H
#define __module_var_H

#include "FreeRTOS.h"

// --- Статические ресурсы для главной задачи ---
extern StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xMainAppTaskTCB;

// --- Статические ресурсы для задачи АЦП ---
extern StackType_t xAdcTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xAdcTaskTCB;

#endif /*__ module_var_H */