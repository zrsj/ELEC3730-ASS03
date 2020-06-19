/*
 *        $Id: Ass-03.h 2171 2020-06-14 22:25:52Z Peter $
 *  $Revision: 2171 $
 *      $Date: 2020-06-15 08:25:52 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

// Header file for all modules

#ifndef ASS_03_H_
#define ASS_03_H_

// Assignment and version strings

#define ASS_STRING "ELEC3730-2020s1 Assignment 3"
#define VER_STRING "Ver: 04 $Rev: 2171 $"

// Standard includes

extern void
initialise_monitor_handles (void); // STEPIEN: To allow printing to console
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "FatFs.h"
#include "sdio.h"

#include "dcmi.h"
#include "dma.h"
#include "fsmc.h"

#include "touch_panel.h"

#include "openx07v_c_lcd.h"
#include "dcmi_ov7670.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// To enable debug messages, uncomment

#define DEBUG(inc) // inc

// Library functions

extern void Init_Camera(void);
extern void Enable_Camera(void);
extern void Swap_SDCard_to_Camera(void);
extern void Swap_Camera_to_SDCard(void);
extern uint8_t BSP_TP_Init (void);
extern uint8_t BSP_TP_GetDisplayPoint (Coordinate *pDisplay);

// OS Handles

extern osMutexId SDIODCMIMutexHandle;
extern osMutexId LCDMutexHandle;
extern osSemaphoreId DCMILineCompleteHandle;

// Task functions

extern void StartControlTask(void const * argument);
extern void StartCameraTask(void const * argument);
extern void StartLCDTask(void const * argument);
extern void StartTPTask(void const * argument);
extern void StartTimeTask(void const * argument);
extern void StartSDTask(void const * argument);

// Message functions for each task

#define MESS_STR_LEN 16

extern void InitLCDTaskMailQueue(void);
extern void TextBoxSend(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *t);
extern void DrawBoxSend(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void InitTPTaskMailQueue(void);
extern void CheckTouch(void);
extern void CheckTouchSend(uint16_t x, uint16_t y);
extern void AddButtonSend(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *t);

// Task functions

extern void StartControlTask(void const * argument);
extern void StartCameraTask(void const * argument);
extern void StartLCDTask(void const * argument);
extern void StartTPTask(void const * argument);
extern void StartTimeTask(void const * argument);
extern void StartSDTask(void const * argument);

#endif /* ASS_03_H_ */

typedef enum{
  nullNum = -1,
  up = 0,
  down = 1,
  view = 2,
  delete = 3,
  live = 4
} tenButtons;

#define ENUM_VALUES 5

struct strButton{
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
};

struct strButton arstrButtons[ENUM_VALUES];