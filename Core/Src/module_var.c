/**
  * @file module.var.cpp
  * @brief Константы и переменные для проекта.
  *
  */

#include "module_var.h"

// --- Статические ресурсы для главное задачи ---
StackType_t xMainAppTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xMainAppTaskTCB;
