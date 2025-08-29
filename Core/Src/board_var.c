/*
 ====================================================================
 = Description:                  Глобальные переменные для проекта
 = File name:                    board_var.c
 ====================================================================
 */

#include "board_var.h"

// --- Статические ресурсы для главное задачи ---
StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xMainAppTaskTCB;

// --- Статические ресурсы для задачи АЦП ---
StackType_t xAdcTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xAdcTaskTCB;
