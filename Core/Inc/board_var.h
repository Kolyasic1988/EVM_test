/*
 ====================================================================
 = Description:                  Глобальные переменные для проекта
 = File name:                    board_var.h
 ====================================================================
 */
#ifndef __board_var_H
#define __board_var_H

#include "FreeRTOS.h"

// --- Статические ресурсы для главной задачи ---
extern StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xMainAppTaskTCB;

// --- Статические ресурсы для задачи АЦП ---
extern StackType_t xAdcTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t xAdcTaskTCB;

#endif /*__ board_var_H */