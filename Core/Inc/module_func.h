/**
  * @file module_func.h
  * @brief Прототипы функций проекта проекта.
  *
  */
#ifndef __module_func_H
#define __module_func_H

// Функции инициализации
extern void vInitUser(void);
extern void vInitUserTasks(void);
extern void vInitMainAppTask(void);
extern void vInitAdcTask(void);

// Функции проверки параметров
extern void vAdcCheckParameters(void);

// --- Таска главной задачи ---
extern void vMainAppTask(void *pvArg);

// --- Таска АЦП ---
extern void vAdcTask(void *pvArg);

#endif /*__ module_func_H */