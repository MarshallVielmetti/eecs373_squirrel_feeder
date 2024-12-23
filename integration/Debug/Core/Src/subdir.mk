################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/camera_handler.c \
../Core/Src/integration.c \
../Core/Src/ir_sensor.c \
../Core/Src/lcd.c \
../Core/Src/load_cell.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/vc0706_driver.c 

OBJS += \
./Core/Src/camera_handler.o \
./Core/Src/integration.o \
./Core/Src/ir_sensor.o \
./Core/Src/lcd.o \
./Core/Src/load_cell.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/vc0706_driver.o 

C_DEPS += \
./Core/Src/camera_handler.d \
./Core/Src/integration.d \
./Core/Src/ir_sensor.d \
./Core/Src/lcd.d \
./Core/Src/load_cell.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/vc0706_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mvielmet/Documents/eecs373_squirrel_feeder/integration/Drivers/LCD/Inc" -I../Drivers/LCD/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/camera_handler.cyclo ./Core/Src/camera_handler.d ./Core/Src/camera_handler.o ./Core/Src/camera_handler.su ./Core/Src/integration.cyclo ./Core/Src/integration.d ./Core/Src/integration.o ./Core/Src/integration.su ./Core/Src/ir_sensor.cyclo ./Core/Src/ir_sensor.d ./Core/Src/ir_sensor.o ./Core/Src/ir_sensor.su ./Core/Src/lcd.cyclo ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/load_cell.cyclo ./Core/Src/load_cell.d ./Core/Src/load_cell.o ./Core/Src/load_cell.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/vc0706_driver.cyclo ./Core/Src/vc0706_driver.d ./Core/Src/vc0706_driver.o ./Core/Src/vc0706_driver.su

.PHONY: clean-Core-2f-Src

