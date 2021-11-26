 /******************************************************************
 *
 * @file	HyvePlatformSensorNum.h
 * @brief	The definition of the Hyve platform sensor number 
 *
 ******************************************************************/

#ifndef HYVEPLATFORMSENSORNUM_H_
#define HYVEPLATFORMSENSORNUM_H_


#define BMC_SENSOR_LUN											(BMC_SENSOR_LUN01)

/********************* LUN 00 *********************/
#define SENSOR_NUM_ALANTEST_LUN00								(0xAA)
#define SENSOR_NUM_PWRUNIT_STATUS								(0x50)

/********************* LUN 01 *********************/
#define SENSOR_NUM_ALANTEST_LUN01								(0xAA)

// Event Only
#define SENSOR_NUM_FW_CHANGE									(0x01)
#define SENSOR_NUM_ACPI_STATUS									(0x02)
#define SENSOR_NUM_WATCHDOG2									(0x03)
#define SENSOR_NUM_MEM_HOT										(0x04)
#define SENSOR_NUM_I2C_BUSHANG									(0x05)
#define SENSOR_NUM_BUTTON										(0x06)
#define SENSOR_NUM_SYS_RESTART									(0x07)





// PSU0
#define SENSOR_NUM_PSU0_STATUS									(0x30)
#define SENSOR_NUM_CURR_PSU0CIN									(0x31)
#define SENSOR_NUM_CURR_PSU0COUT								(0x32)	// current out, need to verify
#define SENSOR_NUM_PWR_PSU0PIN									(0x33)
#define SENSOR_NUM_PWR_PSU0POUT									(0x34)
#define SENSOR_NUM_VOLT_PSU0									(0x35)
#define SENSOR_NUM_TEMP_PSU0									(0x36)
#define SENSOR_NUM_TACH_PSU0Fan0								(0x37)
// PSU1
#define SENSOR_NUM_PSU1_STATUS									(0x38)
#define SENSOR_NUM_CURR_PSU1CIN									(0x39)
#define SENSOR_NUM_CURR_PSU1COUT								(0x3A)	// current out, need to verify
#define SENSOR_NUM_PWR_PSU1PIN									(0x3B)
#define SENSOR_NUM_PWR_PSU1POUT									(0x3C)
#define SENSOR_NUM_VOLT_PSU1									(0x3D)
#define SENSOR_NUM_TEMP_PSU1									(0x3E)
#define SENSOR_NUM_TACH_PSU1Fan0								(0x3F)







// #define SENSOR_NUM_									(0x)



#endif
