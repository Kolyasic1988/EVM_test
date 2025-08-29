/*
 ====================================================================
 = Description:                  Прототипы функций проекта
 = File name:                    board_func.h
 ====================================================================
 */
#ifndef __board_func_H
#define __board_func_H

// Функции инициализации
extern void vInitUser(void);
extern void vInitUserTasks(void);
extern void vInitMainAppTask(void);
extern void vInitAdcTask(void);


// Функции таско
extern void vMainAppTask(void *pvArg);
extern void vAdcTask(void *pvArg);

// Функции обработчики
extern void vRunHandlers(void);
extern void vAdcCheckParameters(void);

#endif /*__ board_func_H */