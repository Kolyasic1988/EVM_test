/*
 ====================================================================
 = Description:                  Прототипы функций проекта
 = File name:                    board_func.h
 ====================================================================
 */
#ifndef __BOARD_FUNC_H
#define __BOARD_FUNC_H

// Функции инициализации
extern void vInitUser(void);
extern void vInitUserTasks(void);
extern void vInitMainAppTask(void);
extern void vInitAdcTask(void);
extern void vInitCanQueue(void);

// Функции задач
extern void vMainAppTask(void *pvArg);
extern void vAdcTask(void *pvArg);

// Функции обработчики
extern void vRunHandlers(void);
extern void vAdcCheckParameters(void);

// Функция запуска таймера АЦП
extern void vStartAdcTimer(void);

#endif /*__BOARD_FUNC_H */