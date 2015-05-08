################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
OT/System_init.obj: ../OT/System_init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.11/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_headers/include" --include_path="E:/ti/controlSUITENew/device_support/F2837xD/v150/F2837xD_common/include" -g --define=CPU1 --define=_FLASH --diag_warning=225 --display_error_number --diag_suppress=10063 --preproc_with_compile --preproc_dependency="OT/System_init.pp" --obj_directory="OT" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


