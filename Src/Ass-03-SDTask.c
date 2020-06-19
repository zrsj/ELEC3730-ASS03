/*
 *        $Id: Ass-03-SDTask.c 2171 2020-06-14 22:25:52Z Peter $
 *  $Revision: 2171 $
 *      $Date: 2020-06-15 08:25:52 +1000 (Mon, 15 Jun 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

#define BUFF_SIZE 128
void ExitError();

void
StartSDTask (void const * argument)
{
  const TCHAR *fn = "FIRST.TXT";
  FIL fd;
  FRESULT res;
  UINT bytesread;
  uint8_t textread[BUFF_SIZE];

  printf ("INFO: Hello from %s!\n", pcTaskGetName (osThreadGetId ()));
  // while (1)
  {
    osDelay(10000);
  }

  // while (1) // Run the read test multiple times
  {

    // Get control
    //
    osMutexWait (SDIODCMIMutexHandle, osWaitForever);
    Swap_Camera_to_SDCard ();
    DEBUG(printf ("INFO: %s has control of shared SDIO/DCMI pins!\n",
            pcTaskGetName (osThreadGetId ()));)

    // Check if SD card driver available (only done once)
    //
    if (retSD != 0)
    {
      printf ("ERROR: SD card driver not available.");
      ExitError();
    }
    DEBUG(printf ("INFO: SD card driver available.\n");)

    // Mount file system (only once after media is installed)
    //
    if ((res = f_mount (&SDFatFS, (TCHAR const *) SDPath, 0)) != FR_OK)
    {
      printf ("ERROR: Could not mount file system '%s' (%d).\n", SDPath, res);
      ExitError();
    }
    DEBUG(printf ("INFO: Mounted file system '%s'\n", SDPath);)

    // Open file
    //
    if ((res = f_open (&fd, fn, FA_READ)) != FR_OK)
    {
      printf ("ERROR: Opening '%s' (%d)\n", fn, res);
      f_mount (0, "", 0); // No error check
      ExitError();
    }
    DEBUG(printf ("INFO: Opened file '%s'\n", fn);)

    // Read data from file
    //
    if ((res = f_read (&fd, &textread, BUFF_SIZE - 1, &bytesread)) != FR_OK)
    {
      printf ("ERROR: Reading '%s' (%d)\n", fn, res);
      f_close (&fd);      // No error check
      f_mount (0, "", 0); // No error check
      ExitError();
    }
    textread[bytesread] = '\0'; // Null terminate string (assume text in file)
    DEBUG(printf ("INFO: Read '%s'\n", textread);)

    // Close file
    //
    if ((res = f_close (&fd)) != FR_OK)
    {
      printf ("ERROR: closing '%s' (%d)\n", fn, res);
      f_mount (0, "", 0); // No error check
      ExitError();
    }
    DEBUG(printf ("INFO: Closed file '%s'\n", fn);)

    // Unmount file system (only required if media is removed)
    //
    if ((res = f_mount (0, "", 0)) != FR_OK)
    {
      printf ("ERROR: Unmounting file system\n");
      ExitError();
    }
    DEBUG(printf ("INFO: File system unmounted\n");)

    // End of example
    //
    DEBUG(printf ("INFO: End of example.\n"));

    // Give back control to camera
    //
    Swap_SDCard_to_Camera ();
    osMutexRelease (SDIODCMIMutexHandle);

    // Wait before looping around again
    //
    osDelay (10000);
  }

  while (1)
  {
    osDelay(10000);
  }

}


// Stop if an error occurs
//
void ExitError()
{

  // Give back control to DCMI interface and release MUTEX
  Swap_SDCard_to_Camera ();
  osMutexRelease (SDIODCMIMutexHandle);

  // Wait forever
  while (1)
    osDelay (1000);

}
