/*
 *        $Id: Ass-03-TimeTask.c 2168 2020-06-14 21:52:43Z Peter $
 *  $Revision: 2168 $
 *      $Date: 2020-06-15 07:52:43 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

uint32_t TheTime = 0;
char TheTimeString[MESS_STR_LEN];

struct {
  uint8_t inSeconds;
  uint8_t inMinutes;
  uint8_t inHours;
  uint32_t inDay;
}strTime;

// struct tstrTime strTime;

void StartTimeTask(void const * argument)
{
	printf("INFO: Hello from %s!\n", pcTaskGetName(osThreadGetId()));
  fnvdTimeInit();
  while (1)
  {
    // STEPIEN: Rough example, need to do accurate time and HH:MM:SS

    if(strTime.inDay < 100){
      sprintf(TheTimeString,"%2dd %2dh %2dm %2ds", strTime.inDay, strTime.inHours, strTime.inMinutes, strTime.inSeconds);
    }else{
      sprintf(TheTimeString,"%4dd %2dh %2dm", strTime.inDay, strTime.inHours, strTime.inMinutes);
    }
    TextBoxSend(100, 210, 210, 20, TheTimeString);
    fnvdIncreaseTime();
	  osDelay(1000);
  }
}

void fnvdTimeInit(void){
  strTime.inSeconds = 0;
  strTime.inMinutes = 0;
  strTime.inHours = 0;
  strTime.inDay = 0;
}

void fnvdIncreaseTime(void){
  strTime.inSeconds++;
  if(strTime.inSeconds == 60){
    strTime.inSeconds = 0;
    strTime.inMinutes++;
  }
  if(strTime.inMinutes == 60){
    strTime.inMinutes = 0;
    strTime.inHours++;
  }
  if(strTime.inHours == 24){
    strTime.inHours = 0;
    strTime.inDay++;
  }
}