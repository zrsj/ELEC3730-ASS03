/*
 *        $Id: Ass-03.h 2155 2020-06-01 20:22:34Z Peter $
 *  $Revision: 2155 $
 *      $Date: 2020-06-02 06:22:34 +1000 (Tue, 02 Jun 2020) $
 *    $Author: Peter $
 */

// Header file for all modules

#ifndef ASS_03_H_
#define ASS_03_H_

// Assignment and version strings

#define ASS_STRING "ELEC3730-2020s1 Assignment 3"
#define VER_STRING "Ver: 03 $Rev: 2155 $"

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

#include "openx07v_c_lcd.h"
#include "dcmi_ov7670.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "LCDTouch.h"

// Library functions

extern void Init_Camera(void);
extern void Enable_Camera(void);
extern void Swap_SDCard_to_Camera(void);
extern void Swap_Camera_to_SDCard(void);

// OS Handles

extern osMutexId SDIODCMIMutexHandle;
extern osSemaphoreId DCMILineCompleteHandle;

// Task functions

extern void StartControlTask(void const * argument);
extern void StartCameraTask(void const * argument);
extern void StartLCDTask(void const * argument);
extern void StartTPTask(void const * argument);
extern void StartTimeTask(void const * argument);
extern void StartSDTask(void const * argument);

#endif /* ASS_03_H_ */
