################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

network_common.obj: ../network_common.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="network_common.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

rom_pin_mux_config.obj: ../rom_pin_mux_config.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="rom_pin_mux_config.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

task_led.obj: ../task_led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="task_led.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

task_uart.obj: ../task_uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="task_uart.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

task_wifi.obj: ../task_wifi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="task_wifi.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: /home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="/home/eric/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/include" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink/source" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/oslib" --include_path="/home/eric/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="uart_if.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


