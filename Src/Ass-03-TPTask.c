/*
 *        $Id: Ass-03-TPTask.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

tenButtons tenButtonDetect(void){
  if(BSP_TP_GetDisplayPoint (&display) == 0){
    for(uint8_t i = 0; i < ENUM_VALUES; i++){
      if((display.x >= arstrButtons[i].x && display.x <= (arstrButtons[i].x + arstrButtons[i].width)) && (display.y >= arstrButtons[i].y && display.y <= (arstrButtons[i].y + arstrButtons[i].height))){ // Defined by the top left corner and the size of the rectangle that it forms
        return i;
      } 
    }    
  }
  return nullNum;
}

void fnvdInitButtonStr(void){
    for(uint8_t i = 0; i < ENUM_VALUES; i++){
      arstrButtons[i].x = 0;
      arstrButtons[i].y = 0;
      arstrButtons[i].width = 0;
      arstrButtons[i].height = 0;
    }
}

void fnvdEnterButton(tenButtons type, uint16_t x, uint16_t y, uint16_t width, uint16_t height){
  arstrButtons[type].x = x;
  arstrButtons[type].y = y;
  arstrButtons[type].width = width;
  arstrButtons[type].height = height; 
}

void StartTPTask(void const * argument)
{
  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  BSP_TP_Init ();
  fnvdInitButtonStr();
  tenButtons enPressed = nullNum;
  while (1)
  {
    enPressed = tenButtonDetect();
	  osDelay(1);
  }
}

