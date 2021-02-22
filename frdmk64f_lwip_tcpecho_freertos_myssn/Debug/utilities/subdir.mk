################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\board" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\source" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\drivers" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\device" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\CMSIS" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\contrib\apps\tcpecho" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\port\arch" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\compat\posix\arpa" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\compat\posix\net" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\compat\posix" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\compat\posix\sys" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\compat\stdc" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\lwip" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\lwip\priv" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\lwip\prot" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\netif" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\netif\ppp" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include\netif\ppp\polarssl" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\port" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\amazon-freertos\freertos_kernel\include" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\utilities" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\component\serial_manager" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\component\lists" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\component\uart" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src" -I"C:\Users\josue\Documents\MCUXpressoIDE_11.2.0_4120\workspaceKaty\frdmk64f_lwip_tcpecho_freertos_myssn\lwip\src\include" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


