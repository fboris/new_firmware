#ifndef __QUADCOPTER_CONFIG_H
#define __QUADCOPTER_CONFIG_H

/* Hardware environments */
/* Radio Control */
#define USE_FUTABA_CONTROLLER		1
#define USE_WFLY_CONTROLLER		0

/* Status report functions */
#define configSTATUS_SHELL		1

/* Set baudrate */
#define Serial_Baudrate 57600

/* Includes */
//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//FatFS
#include "diskio.h"
#include "ff.h"

//Algorithm
#include "PID.h"
#include "moving_average.h"
#include "quaternion.h"
#include "_math.h"

//System
#include "main.h"
#include "global.h"
#include "std.h"
#include "AHRS.h"
#include "remote_control.h"
#include "IMU_correct.h"
#include "communication.h"

//Driver
#include "stm32f4_system.h"
#include "stm32f4xx_conf.h"
#include "delay.h"
#include "flash.h"
#include "i2c.h"
#include "spi.h"
#include "sdio.h"
#include "led.h"
#include "motor.h"
#include "mpu9150.h"
#include "ms5611.h"
#include "serial.h"
#include "sensor.h"

//Shell
#include "linenoise.h"
#include "shell.h"
#include "parser.h"
#include "watch.h"

//Debugger
#include "test.h"

#endif
