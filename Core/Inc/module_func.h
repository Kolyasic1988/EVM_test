/**
  * @file module_func.h
  * @brief Прототипы функций проекта проекта.
  *
  */
#ifndef __module_func_H
#define __module_func_H

// Функции инициализации
void vInitUser(void);
void vInitUserTasks(void);
void Init_MainAppTask(void);

// Функции проверки параметров
void vAdcCheckParameters(void);
void vCheckTermistorTemp(void);

// --- Таска главной задачи ---
void vMainAppTask(void *pvArg);

#endif /*__ module_func_H */