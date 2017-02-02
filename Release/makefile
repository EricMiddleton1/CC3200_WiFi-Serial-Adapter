################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS

GEN_OPTS__FLAG := --cmd_file="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/linker.cmd"

ORDERED_OBJS += \
"./main.obj" \
"./network_common.obj" \
"./rom_pin_mux_config.obj" \
"./task_led.obj" \
"./task_uart.obj" \
"./task_wifi.obj" \
"./uart_if.obj" \
"../cc3200v1p32.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib/ccs/ti_rtos/ti_rtos.a" \
-l"/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/ccs/OS/simplelink.a" \
-l"/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib/ccs/Release/driverlib.a" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
CC3200_WiFi-Serial-Adapter.out \

EXE_OUTPUTS__QUOTED += \
"CC3200_WiFi-Serial-Adapter.out" \

BIN_OUTPUTS += \
CC3200_WiFi-Serial-Adapter.bin \

BIN_OUTPUTS__QUOTED += \
"CC3200_WiFi-Serial-Adapter.bin" \


# All Target
all: CC3200_WiFi-Serial-Adapter.out

dependents:
	-cd /home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default && $(MAKE) all

# Tool invocations
CC3200_WiFi-Serial-Adapter.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) /home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/ti_rtos_config.lib
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number -z -m"CC3200_WiFi-Serial-Adapter.map" --heap_size=0x1000 --stack_size=0x800 -i"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/lib" -i"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --reread_libs --display_error_number --diag_wrap=off --warn_sections --xml_link_info="CC3200_WiFi-Serial-Adapter_linkInfo.xml" --rom_model -o "CC3200_WiFi-Serial-Adapter.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

CC3200_WiFi-Serial-Adapter.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armhex"  -o "CC3200_WiFi-Serial-Adapter.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "network_common.obj" "rom_pin_mux_config.obj" "task_led.obj" "task_uart.obj" "task_wifi.obj" "uart_if.obj" 
	-$(RM) "main.d" "network_common.d" "rom_pin_mux_config.d" "task_led.d" "task_uart.d" "task_wifi.d" "uart_if.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"/home/eric/ti/ccsv7/utils/tiobj2bin/tiobj2bin" "CC3200_WiFi-Serial-Adapter.out" "CC3200_WiFi-Serial-Adapter.bin" "/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armofd" "/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armhex" "/home/eric/ti/ccsv7/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/ti_rtos_config.lib:

-include ../makefile.targets

