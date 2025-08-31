
/*
 ====================================================================
 = Description:                  Прототипы функций проекта
 = File name:                    board_func.h
 ====================================================================
 */
#ifndef __BOARD_FUNC_H
#define __BOARD_FUNC_H

#include "board_def.h"

extern void vInitUser(void);
extern void vInitxState(void);
extern void vInitUserTasks(void);
extern void vInitMainAppTask(void);
extern void vInitAdcTask(void);
extern void vInitCanQueue(void);

extern void vMainAppTask(void *pvArg);
extern void vAdcTask(void *pvArg);

extern void vRunHandlers(void);
extern void vAdcCheckParameters(void);

extern void vStartAdcTimer(void);

#endif /*__BOARD_FUNC_H */