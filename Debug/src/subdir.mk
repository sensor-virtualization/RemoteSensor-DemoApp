################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AppResourceId.cpp \
../src/SensorApp.cpp \
../src/SensorAppEntry.cpp \
../src/SensorAppFormFactory.cpp \
../src/SensorAppFrame.cpp \
../src/SensorAppMainForm.cpp \
../src/SensorAppPanelFactory.cpp \
../src/SensorsAppAccelForm.cpp \
../src/SensorsAppGravityForm.cpp \
../src/SensorsAppGyroForm.cpp \
../src/SensorsAppLightForm.cpp \
../src/SensorsAppMagneticForm.cpp \
../src/SensorsAppOrientationForm.cpp \
../src/SensorsAppProximityForm.cpp \
../src/SensorsAppRemoteGyroForm.cpp \
../src/SensorsAppTiltForm.cpp \
../src/SensorsAppUserAccelForm.cpp 

OBJS += \
./src/AppResourceId.o \
./src/SensorApp.o \
./src/SensorAppEntry.o \
./src/SensorAppFormFactory.o \
./src/SensorAppFrame.o \
./src/SensorAppMainForm.o \
./src/SensorAppPanelFactory.o \
./src/SensorsAppAccelForm.o \
./src/SensorsAppGravityForm.o \
./src/SensorsAppGyroForm.o \
./src/SensorsAppLightForm.o \
./src/SensorsAppMagneticForm.o \
./src/SensorsAppOrientationForm.o \
./src/SensorsAppProximityForm.o \
./src/SensorsAppRemoteGyroForm.o \
./src/SensorsAppTiltForm.o \
./src/SensorsAppUserAccelForm.o 

CPP_DEPS += \
./src/AppResourceId.d \
./src/SensorApp.d \
./src/SensorAppEntry.d \
./src/SensorAppFormFactory.d \
./src/SensorAppFrame.d \
./src/SensorAppMainForm.d \
./src/SensorAppPanelFactory.d \
./src/SensorsAppAccelForm.d \
./src/SensorsAppGravityForm.d \
./src/SensorsAppGyroForm.d \
./src/SensorsAppLightForm.d \
./src/SensorsAppMagneticForm.d \
./src/SensorsAppOrientationForm.d \
./src/SensorsAppProximityForm.d \
./src/SensorsAppRemoteGyroForm.d \
./src/SensorsAppTiltForm.d \
./src/SensorsAppUserAccelForm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	clang++.exe -I"pch" -D_DEBUG -I"D:\tizen\workplace\NativeSensorApp\inc" -O0 -g3 -Wall -c -fmessage-length=0 -target i386-tizen-linux-gnueabi -gcc-toolchain "D:/tizen/tizen-sdk/tools/smart-build-interface/../i386-linux-gnueabi-gcc-4.5/" -ccc-gcc-name i386-linux-gnueabi-g++ -march=i386 -Wno-gnu -fPIE --sysroot="D:/tizen/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native" -I"D:/tizen/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include/libxml2" -I"D:\tizen\tizen-sdk\library" -I"D:/tizen/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include" -I"D:/tizen/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-emulator-2.2.native/usr/include/osp" -D_APP_LOG -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


