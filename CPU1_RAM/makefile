################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/c2000_6.2.11

ORDERED_OBJS += \
"./F2837xD_Adc.obj" \
"./F2837xD_CodeStartBranch.obj" \
"./F2837xD_CpuTimers.obj" \
"./F2837xD_DefaultISR.obj" \
"./F2837xD_EPwm.obj" \
"./F2837xD_GlobalVariableDefs.obj" \
"./F2837xD_Gpio.obj" \
"./F2837xD_Ipc.obj" \
"./F2837xD_PieCtrl.obj" \
"./F2837xD_PieVect.obj" \
"./F2837xD_SysCtrl.obj" \
"./F2837xD_usDelay.obj" \
"./InterruptServiceRoutines.obj" \
"./Main.obj" \
"./System_init.obj" \
"./ot_adc.obj" \
"./ot_gpio.obj" \
"./ot_pid.obj" \
"./ot_pwm.obj" \
"./TI/adc.obj" \
"./TI/clk.obj" \
"./TI/cpu.obj" \
"./TI/filter_fo.obj" \
"./TI/gpio.obj" \
"./TI/pid.obj" \
"./TI/pwm.obj" \
"./TI/wdog.obj" \
"E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/lib/SFO_v8_fpu_lib_build_c28.lib" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"rts2800_fpu32.lib" \
-l"2837xD_RAM_lnk_cpu1.cmd" \
-l"F2837xD_Headers_nonBIOS_cpu1.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include TI/subdir_vars.mk
-include subdir_rules.mk
-include TI/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
BuckPIDTestV2.out \

EXE_OUTPUTS__QUOTED += \
"BuckPIDTestV2.out" \

BIN_OUTPUTS += \
BuckPIDTestV2.hex \

BIN_OUTPUTS__QUOTED += \
"BuckPIDTestV2.hex" \


# All Target
all: BuckPIDTestV2.out

# Tool invocations
BuckPIDTestV2.out: $(OBJS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 -z -m"BuckPIDTestV2.map" --stack_size=0x100 --warn_sections -i"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/lib" -i"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" -i"E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/cmd" -i"E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/cmd" --reread_libs --display_error_number --xml_link_info="BuckPIDTestV2_linkInfo.xml" --entry_point=code_start --rom_model -o "BuckPIDTestV2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

BuckPIDTestV2.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/hex2000"  -o "BuckPIDTestV2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "F2837xD_Adc.pp" "F2837xD_CpuTimers.pp" "F2837xD_DefaultISR.pp" "F2837xD_EPwm.pp" "F2837xD_GlobalVariableDefs.pp" "F2837xD_Gpio.pp" "F2837xD_Ipc.pp" "F2837xD_PieCtrl.pp" "F2837xD_PieVect.pp" "F2837xD_SysCtrl.pp" "InterruptServiceRoutines.pp" "Main.pp" "System_init.pp" "ot_adc.pp" "ot_gpio.pp" "ot_pid.pp" "ot_pwm.pp" "TI\adc.pp" "TI\clk.pp" "TI\cpu.pp" "TI\filter_fo.pp" "TI\gpio.pp" "TI\pid.pp" "TI\pwm.pp" "TI\wdog.pp" 
	-$(RM) "F2837xD_Adc.obj" "F2837xD_CodeStartBranch.obj" "F2837xD_CpuTimers.obj" "F2837xD_DefaultISR.obj" "F2837xD_EPwm.obj" "F2837xD_GlobalVariableDefs.obj" "F2837xD_Gpio.obj" "F2837xD_Ipc.obj" "F2837xD_PieCtrl.obj" "F2837xD_PieVect.obj" "F2837xD_SysCtrl.obj" "F2837xD_usDelay.obj" "InterruptServiceRoutines.obj" "Main.obj" "System_init.obj" "ot_adc.obj" "ot_gpio.obj" "ot_pid.obj" "ot_pwm.obj" "TI\adc.obj" "TI\clk.obj" "TI\cpu.obj" "TI\filter_fo.obj" "TI\gpio.obj" "TI\pid.obj" "TI\pwm.obj" "TI\wdog.obj" 
	-$(RM) "F2837xD_CodeStartBranch.pp" "F2837xD_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

