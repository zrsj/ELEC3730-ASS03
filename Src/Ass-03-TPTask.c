/*
 *        $Id: Ass-03-TPTask.c 2168 2020-06-14 21:52:43Z Peter $
 *  $Revision: 2168 $
 *      $Date: 2020-06-15 07:52:43 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

char TheTouchString[MESS_STR_LEN];

struct strButton buttonUp = {
  5, 30, 80, 20, "UP"
},
buttonDown = {
  5, 55, 80, 20, "DOWN"
};

void StartTPTask(void const * argument)
{
  printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  while (1)
  {
    // DrawBoxSend((display.x - 5),(display.y - 5), 10, 10);
    fnvdButtonHandler(&buttonUp);
    fnvdButtonHandler(&buttonDown);
    if (BSP_TP_GetDisplayPoint (&display) == 0)
    {
      sprintf(TheTouchString,"(%3d, %3d)", display.x, display.y);
      TextBoxSend(5, 5, 160, 20, TheTouchString);
    }
	  osDelay(100);
  }
}

void fnvdButtonHandler(struct strButton *input){
  if((display.x > input->x && display.x < (input->x + input->width)) && (display.y > input->y && display.y < (input->y + input->height))){
    TextBoxSend(input->x, input->y, input->width, input->height, "      ");
  }else{
    TextBoxSend(input->x, input->y, input->width, input->height, input->name);
  }
}

