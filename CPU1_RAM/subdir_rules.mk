################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837xD_Adc.obj: ../F2837xD_Adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_Adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_CodeStartBranch.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_CpuTimers.obj: E:/ti/controlSUITE.MARCH20/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_CpuTimers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_CpuTimers.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_DefaultISR.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_DefaultISR.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_DefaultISR.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_EPwm.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_EPwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_EPwm.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_GlobalVariableDefs.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_Gpio.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_Gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_Gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_Ipc.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_Ipc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_Ipc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_PieCtrl.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_PieCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_PieCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_PieVect.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_PieVect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_PieVect.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_SysCtrl.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_usDelay.obj: E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/source/F2837xD_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

InterruptServiceRoutines.obj: ../InterruptServiceRoutines.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="InterruptServiceRoutines.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main.obj: ../Main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="Main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

System_init.obj: ../System_init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="System_init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ot_adc.obj: ../ot_adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="ot_adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ot_gpio.obj: ../ot_gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="ot_gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ot_pid.obj: ../ot_pid.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="ot_pid.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ot_pwm.obj: ../ot_pwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="ot_pwm.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


