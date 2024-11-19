################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ili9341/Src/ILI9341_GFX.c \
../Drivers/ili9341/Src/ILI9341_STM32_Driver.c 

OBJS += \
./Drivers/ili9341/Src/ILI9341_GFX.o \
./Drivers/ili9341/Src/ILI9341_STM32_Driver.o 

C_DEPS += \
./Drivers/ili9341/Src/ILI9341_GFX.d \
./Drivers/ili9341/Src/ILI9341_STM32_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ili9341/Src/%.o Drivers/ili9341/Src/%.su Drivers/ili9341/Src/%.cyclo: ../Drivers/ili9341/Src/%.c Drivers/ili9341/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"N:/EECS373/LCD_test/Drivers/hx8357d/inc" -I"N:/EECS373/LCD_test/Drivers/ili9341/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ili9341-2f-Src

clean-Drivers-2f-ili9341-2f-Src:
	-$(RM) ./Drivers/ili9341/Src/ILI9341_GFX.cyclo ./Drivers/ili9341/Src/ILI9341_GFX.d ./Drivers/ili9341/Src/ILI9341_GFX.o ./Drivers/ili9341/Src/ILI9341_GFX.su ./Drivers/ili9341/Src/ILI9341_STM32_Driver.cyclo ./Drivers/ili9341/Src/ILI9341_STM32_Driver.d ./Drivers/ili9341/Src/ILI9341_STM32_Driver.o ./Drivers/ili9341/Src/ILI9341_STM32_Driver.su

.PHONY: clean-Drivers-2f-ili9341-2f-Src

