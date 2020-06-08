################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Fonts/font12.c \
../Drivers/BSP/Fonts/font16.c \
../Drivers/BSP/Fonts/font20.c \
../Drivers/BSP/Fonts/font24.c \
../Drivers/BSP/Fonts/font8.c 

OBJS += \
./Drivers/BSP/Fonts/font12.o \
./Drivers/BSP/Fonts/font16.o \
./Drivers/BSP/Fonts/font20.o \
./Drivers/BSP/Fonts/font24.o \
./Drivers/BSP/Fonts/font8.o 

C_DEPS += \
./Drivers/BSP/Fonts/font12.d \
./Drivers/BSP/Fonts/font16.d \
./Drivers/BSP/Fonts/font20.d \
./Drivers/BSP/Fonts/font24.d \
./Drivers/BSP/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Fonts/%.o: ../Drivers/BSP/Fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP/Fonts" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


