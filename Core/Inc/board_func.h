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


// Функции таско
extern void vMainAppTask(void *pvArg);
extern void vAdcTask(void *pvArg);

// Функции обработчики
extern void vRunHandlers(void);
extern void vAdcCheckParameters(void);

#endif /*__BOARD_FUNC_H */