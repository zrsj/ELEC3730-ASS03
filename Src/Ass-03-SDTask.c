/*
 *        $Id: Ass-03-SDTask.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

void
StartSDTask (void const * argument)
{
#define BUFF_SIZE 128
  const TCHAR *fn = "FIRST.TXT";
  FIL fd;
  FRESULT res;
  UINT bytesread;
  uint8_t textread[BUFF_SIZE];

  printf ("INFO: Hello from %s!\n", pcTaskGetName (osThreadGetId ()));

  while (1)
  {

    // Get control
    //
    osMutexWait (SDIODCMIMutexHandle, osWaitForever);
    Swap_Camera_to_SDCard ();
    printf ("INFO: %s has control of shared SDIO/DCMI pins!\n",
            pcTaskGetName (osThreadGetId ()));

    // Check if SD card driver available (only done once)
    //
    if (retSD != 0)
    {
      printf ("ERROR: SD card driver not available.");
      while (1)
        ; // return 1;
    }
    printf ("INFO: SD card driver available.\n");

    // Mount file system (only once after media is installed)
    //
    if ((res = f_mount (&SDFatFS, (TCHAR const *) SDPath, 0)) != FR_OK)
    {
      printf ("ERROR: Could not mount file system '%s' (%d).\n", SDPath, res);
      while (1); // return 1;
    }
    printf ("INFO: Mounted file system '%s'\n", SDPath);

    // Open file
    //
    if ((res = f_open (&fd, fn, FA_READ)) != FR_OK)
    {
      printf ("ERROR: Opening '%s' (%d)\n", fn, res);
      f_mount (0, "", 0); // No error check
      while (1)
        osDelay (1000); // return 1;
    }
    printf ("INFO: Opened file '%s'\n", fn);

    // Read data from file
    //
    if ((res = f_read (&fd, &textread, BUFF_SIZE - 1, &bytesread)) != FR_OK)
    {
      printf ("ERROR: Reading '%s' (%d)\n", fn, res);
      f_close (&fd);      // No error check
      f_mount (0, "", 0); // No error check
      while (1); // return 1;
    }
    textread[bytesread] = '\0'; // Null terminate string (assume text in file)
    printf ("INFO: Read '%s'\n", textread);

    // Close file
    //
    if ((res = f_close (&fd)) != FR_OK)
    {
      printf ("ERROR: closing '%s' (%d)\n", fn, res);
      f_mount (0, "", 0); // No error check
      while (1); // return 1;
    }
    printf ("INFO: File '%s' closed\n", fn);

    // Unmount file system (only required if media is removed)
    //
    if ((res = f_mount (0, "", 0)) != FR_OK)
    {
      printf ("ERROR: Unmounting file system\n");
      while (1); // return 1;
    }
    printf ("INFO: File system unmounted\n");

    // End of example
    //
    printf ("INFO: End of example.\n");

    // Give back control to camera
    //
    Swap_SDCard_to_Camera ();
    osMutexRelease (SDIODCMIMutexHandle);

    // Wait before looping around again
    //
    osDelay (5000);
  }
}
