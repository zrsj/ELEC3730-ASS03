/*
 *        $Id: Ass-03-LCDTask.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

void StartLCDTask(void const * argument)
{
	printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  while (1)
  {
	  osDelay(1000);
  }
}


void fnvdLCDInit(void){
  BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  BSP_LCD_Clear(LCD_COLOR_BLACK); 
}

void fnvdDrawButtons(void){
  for(uint16_t i = 0; i < ENUM_VALUES; i++){
      if(arstrButtons[i].width != 0 || arstrButtons[i].height != 0){
        BSP_LCD_FillRect (arstrButtons[i].x, arstrButtons[i].y, arstrButtons[i].width, arstrButtons[i].height);
      }
  }
}