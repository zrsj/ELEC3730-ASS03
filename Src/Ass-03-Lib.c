/*        $Id: Ass-03-Lib.c 2171 2020-06-14 22:25:52Z Peter $
 *  $Revision: 2171 $
 *      $Date: 2020-06-15 08:25:52 +1000 (Mon, 15 Jun 2020) $
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

	  DEBUG(printf("INFO: Enable DCMI pins...\n");)
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  // Finish message

	  DEBUG(printf("INFO: Camera now connected!\n");)
}

void Swap_Camera_to_SDCard(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Disable camera driver

    DEBUG(printf("INFO: Put DCMI into soft sleep mode\n");)
	if (DCMI_SingleRandomWrite(OV7670_COM2, SOFT_SLEEP_MODE) != 0)
	{
	  printf("ERROR: Cannot put DCMI into soft sleep mode\n");
	}

    // Change the functions of PC8 and PC9 from DCMI to SDIO (SDIO_D0/1).

	DEBUG(printf("INFO: Swapping pin function DCMI to SDIO...\n");)
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Enable SD interface

	DEBUG(printf("INFO: Enabling SDIO...\n");)
	while (hsd.State == HAL_SD_STATE_BUSY) // Check the device is not busy
	{
		  osThreadYield();
	}
	__HAL_SD_ENABLE(&hsd); // Enable the interface (turns on clock)

    // Finish message

	DEBUG(printf("INFO: SD Card now connected!\n"));

}

void Swap_SDCard_to_Camera(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  // Disable the SDIO interface

	  DEBUG(printf("INFO: Disabling SDIO...\n");)
	  while (hsd.State == HAL_SD_STATE_BUSY) // Check the device is not busy
	  {
		  osThreadYield();
	  }
	  __HAL_SD_DISABLE(&hsd); // Disable the interface (turns off clock)

	  // Change the functions of PC8 and PC9 from SDIO to DCMI (DCMI_D2/3).

	  DEBUG(printf("INFO: Swapping pin function SDIO to DCMI...\n"));
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  // Enable camera driver

	  DEBUG(printf("INFO: Take DCMI out of soft sleep mode\n");)
	  if (DCMI_SingleRandomWrite(OV7670_COM2, ODCAP_4x) != 0)
	  {
		  printf("ERROR: Cannot take DCMI out of soft sleep mode\n");
	  }

	  // Finish message

	  DEBUG(printf("INFO: Camera now connected!\n");)
}

// STEPIEN: Added two touch panel functions to make the interface more
//          consistent with the LCD BSP.

uint8_t
BSP_TP_Init (void)
{
  // Initialise the interface and calibrate
  TP_Init (); // This is an empty function since done by STM32CubeMX
  TouchPanel_Calibrate ();

  return 0;
}

uint8_t
BSP_TP_GetDisplayPoint (Coordinate *pDisplay)
{
  Coordinate *pScreen;

  pScreen = Read_Ads7846 ();
  if (pScreen == NULL)
  {
    return 1; // Error reading the touch panel
  }
  if (getDisplayPoint (pDisplay, pScreen, &matrix) == DISABLE)
  {
    return 1; // Error in LCD
  }
  return 0;
}

void fnvdLCDInit(void){
  // BSP_LCD_Init();
  BSP_LCD_DisplayOn();
  //  
}


/*
void fnvdDrawButtons(void){
  // LCD_IO_WriteReg(LCD_REG_34); 
  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  for(uint16_t i = 0; i < ENUM_VALUES; i++){
      if(arstrButtons[i].width != 0 || arstrButtons[i].height != 0){        
        BSP_LCD_FillRect (arstrButtons[i].x, arstrButtons[i].y, arstrButtons[i].width, arstrButtons[i].height);
      }
  }
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


void fnvdEnterValuesButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, tenButtons type){
      arstrButtons[type].x = x;
      arstrButtons[type].y = y;
      arstrButtons[type].width = width;
      arstrButtons[type].height = height;
}
*/


