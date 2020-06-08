################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/BSP/Fonts" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Drivers/CMSIS/Include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/benja/Documents/year2/sem1/elec3730/ELEC3730-2020s1-Ass-03-Template-v03/Ass-03/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


