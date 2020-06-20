/*
 *        $Id: Ass-03-TPTask.c 2168 2020-06-14 21:52:43Z Peter $
 *  $Revision: 2168 $
 *      $Date: 2020-06-15 07:52:43 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

char TheTouchString[MESS_STR_LEN];

struct strButton buttonUp = {
  5, 30, 80, 20, 0, "UP"
},
buttonDown = {
  5, 55, 80, 20, 0, "DOWN"
},
buttonView = {
  5, 80, 80, 20, 0, "VIEW" 
},
buttonDelete = {
  5, 105, 80, 20, 0, "DELETE" 
},
buttonLive = {
  5, 130, 80, 20, 0, "LIVE" 
},
buttonReset = {
  5, 210, 80, 20, 0, "RESET" 
};

void StartTPTask(void const * argument)
{
  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  fnvdBulkHandler();
  while (1)
  {
    if (BSP_TP_GetDisplayPoint (&display) == 0)
    {
      fnvdBulkHandler();
      if(buttonReset.pressed){
        BSP_LCD_Clear(0xFFFFFFFF);
        fnvdResetTouch();
        fnvdBulkHandler();
        continue;
      }
      sprintf(TheTouchString,"(%3d, %3d)", display.x, display.y);
      TextBoxSend(5, 5, 160, 20, TheTouchString);
    }
    fnvdResetTouch();
	  osDelay(100);
  }
}

void fnvdButtonHandler(struct strButton *input){
  if((display.x > input->x && display.x < (input->x + input->width)) && (display.y > input->y && display.y < (input->y + input->height))){
    TextBoxSend(input->x, input->y, input->width, input->height, "      ");
    input->pressed = 1;
  }else{
    TextBoxSend(input->x, input->y, input->width, input->height, input->name);
    input->pressed = 0;
  }
}

void fnvdBulkHandler(void){
  fnvdButtonHandler(&buttonUp);
  fnvdButtonHandler(&buttonDown);
  fnvdButtonHandler(&buttonView);
  fnvdButtonHandler(&buttonDelete);
  fnvdButtonHandler(&buttonLive);
  fnvdButtonHandler(&buttonReset);
}

void fnvdResetTouch(void){
  display.x = -1;
  display.y = -1;
}