/*        $Id: Ass-03-Lib.c 2139 2020-05-28 22:20:37Z Peter $
 *  $Revision: 2139 $
 *      $Date: 2020-05-29 08:20:37 +1000 (Fri, 29 May 2020) $
 *    $Author: Peter $
 */

#include "Ass-03.h"

// Library files

void Init_Camera(void)
{
  OV7670_IDTypeDef OV7670ID;

  // Read  the camera ID to give confidence that the I2C interface is working correctly

  if(DCMI_OV7670_ReadID(&OV7670ID) == 0)
  {
    printf("INFO: OV7670 ID = 0x%x 0x%x 0x%x 0x%x\n",OV7670ID.Manufacturer_ID1, OV7670ID.Manufacturer_ID2, OV7670ID.PID, OV7670ID.Version);
  }
  else
  {
    printf("ERROR: Reading ID\n");
  }

  printf("INFO: Initialise OV7670\n");
  if (DCMI_OV7670_Init() != 0)
  {
    printf("ERROR: OV7670 initialisation failed\n");
  }
}

void Enable_Camera(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  // Change the functions of PC8 and PC9 from SDIO to DCMI (DCMI_D2/3).

	  printf("INFO: Enable DCMI pins...\n");
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  // Finish message

	  printf("INFO: Camera now connected!\n");
}

void Swap_Camera_to_SDCard(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Disable camera driver

    printf("INFO: Put DCMI into soft sleep mode\n");
	if (DCMI_SingleRandomWrite(OV7670_COM2, SOFT_SLEEP_MODE) != 0)
	{
	  printf("ERROR: Cannot put DCMI into soft sleep mode\n");
	}

    // Change the functions of PC8 and PC9 from DCMI to SDIO (SDIO_D0/1).

	printf("INFO: Swapping pin function DCMI to SDIO...\n");
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Enable SD interface

	printf("INFO: Enabling SDIO...\n");
	while (hsd.State == HAL_SD_STATE_BUSY) // Check the device is not busy
	{
		  osThreadYield();
	}
	__HAL_SD_ENABLE(&hsd); // Enable the interface (turns on clock)

    // Finish message

	printf("INFO: SD Card now connected!\n");

}

void Swap_SDCard_to_Camera(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  // Disable the SDIO interface

	  printf("INFO: Disabling SDIO...\n");
	  while (hsd.State == HAL_SD_STATE_BUSY) // Check the device is not busy
	  {
		  osThreadYield();
	  }
	  __HAL_SD_DISABLE(&hsd); // Disable the interface (turns off clock)

	  // Change the functions of PC8 and PC9 from SDIO to DCMI (DCMI_D2/3).

	  printf("INFO: Swapping pin function SDIO to DCMI...\n");
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  // Enable camera driver

	  printf("INFO: Take DCMI out of soft sleep mode\n");
	  if (DCMI_SingleRandomWrite(OV7670_COM2, ODCAP_1x) != 0)
	  {
		  printf("ERROR: Cannot take DCMI out of soft sleep mode\n");
	  }

	  // Finish message

	  printf("INFO: Camera now connected!\n");
}
