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


/********************* LUN 01 *********************/
// Event Only
#define SENSOR_NUM_FW_CHANGE									(0x01)
#define SENSOR_NUM_ACPI_STATUS									(0x02)
#define SENSOR_NUM_WATCHDOG2									(0x03)	// TODO
#define SENSOR_NUM_I2C_BUSHANG									(0x04)	// TODO
#define SENSOR_NUM_SYS_RESTART									(0x05)
#define SENSOR_NUM_PWRUNIT_STATUS								(0x06)
#define SENSOR_NUM_BMC_RESET									(0x07)
#define SENSOR_NUM_BMC_SEL_STATUS								(0x08)

/* TODO:
About MEM_HOT, this event sensor should be type 0x0c (memory), sensor specific offset 0x0A
#define SENSOR_NUM_MEM_HOT										(???)

About BUTTON, currently doesn't know how to define it
#define SENSOR_NUM_BUTTON										(???)

*/


#define SENSOR_NUM_PMBUS_ALERT									(0x29)
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

// Voltage (ADC)
#define SENSOR_NUM_VOLT_P12V									(0x40)
#define SENSOR_NUM_VOLT_PDBP12V									(0x41)
#define SENSOR_NUM_VOLT_PDBP3V3									(0x42)
#define SENSOR_NUM_VOLT_P3V3									(0x43)
#define SENSOR_NUM_VOLT_P0VDD3V3								(0x44)
#define SENSOR_NUM_VAUX_P5V										(0x45)
#define SENSOR_NUM_VOLT_P0VDD1V8								(0x46)
#define SENSOR_NUM_VOLT_BATP3V									(0x47)
#define SENSOR_NUM_VOLT_P0VDD1V1								(0x48)
#define SENSOR_NUM_VOLT_P0VDDIO									(0x49)
#define SENSOR_NUM_VOLT_P0VDDSOC								(0x4A)
#define SENSOR_NUM_VOLT_P0VDDCORE0								(0x4B)
#define SENSOR_NUM_VOLT_P0VDDCORE1								(0x4C)
#define SENSOR_NUM_VAUX_P12V									(0x4D)
#define SENSOR_NUM_VAUX_P3V3									(0x4E)

// MB Temp. Sensor
// TODO: Currently not define the sensor name
#define SENSOR_NUM_TEMP_MB_1									(0x50) // THERMAL SENSOR 1, ADDR 0x92
#define SENSOR_NUM_TEMP_MB_2									(0x51) // THERMAL SENSOR 2, ADDR 0x94
#define SENSOR_NUM_TEMP_MB_3_0									(0x52) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_1									(0x53) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_2									(0x54) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_3									(0x55) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_4									(0x56) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_5									(0x57) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_6									(0x58) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_7									(0x59) // THERMAL DIODE SENSOR, ADDR 0x90
#define SENSOR_NUM_TEMP_MB_3_8									(0x5A) // THERMAL DIODE SENSOR, ADDR 0x90

/* 1 CPU    12 DIMM    3 VR */
// CPU
#define SENSOR_NUM_TEMP_CPU0									(0x5B)
#define SENSOR_NUM_PWR_CPU0										(0x5C)

// DIMM
#define SENSOR_NUM_TEMP_DIMMA0									(0x5D)
#define SENSOR_NUM_TEMP_DIMMB0									(0x5E)
#define SENSOR_NUM_TEMP_DIMMC0									(0x5F)
#define SENSOR_NUM_TEMP_DIMMD0									(0x60)
#define SENSOR_NUM_TEMP_DIMME0									(0x61)
#define SENSOR_NUM_TEMP_DIMMF0									(0x62)
#define SENSOR_NUM_TEMP_DIMMG0									(0x63)
#define SENSOR_NUM_TEMP_DIMMH0									(0x64)
#define SENSOR_NUM_TEMP_DIMMI0									(0x65)
#define SENSOR_NUM_TEMP_DIMMJ0									(0x66)
#define SENSOR_NUM_TEMP_DIMMK0									(0x67)
#define SENSOR_NUM_TEMP_DIMML0									(0x68)

// VR
#define SENSOR_NUM_TEMP_P0SOCVR0								(0x69) // CPU SOC VR  // P0_VDD_SOC_RUN
#define SENSOR_NUM_TEMP_P0V11VR0								(0x6A) // CPU 1.1 Volt VR // P0_VDD_11_SUS
#define SENSOR_NUM_TEMP_P0IOVR0									(0x6B) // CPU VDDIO VR // P0_VDD_VDDIO_RUN

#define SENSOR_NUM_PWR_P0SOCVR0POUT								(0x6C) // CPU SOC VR  // P0_VDD_SOC_RUN
#define SENSOR_NUM_PWR_P0V11VR0POUT								(0x6D) // CPU 1.1 Volt VR // P0_VDD_11_SUS
#define SENSOR_NUM_PWR_P0IOVR0POUT								(0x6E) // CPU VDDIO VR // P0_VDD_VDDIO_RUN

// Fan
#define SENSOR_NUM_TACH_Fan0									(0x70)
#define SENSOR_NUM_TACH_Fan1									(0x71)
#define SENSOR_NUM_TACH_Fan2									(0x72)
#define SENSOR_NUM_TACH_Fan3									(0x73)
#define SENSOR_NUM_TACH_Fan4									(0x74)
#define SENSOR_NUM_TACH_Fan5									(0x75)
#define SENSOR_NUM_TACH_Fan6									(0x76)
#define SENSOR_NUM_TACH_Fan7									(0x77)

#define SENSOR_NUM_TEMP_FAN_BOARD								(0x78)

// Front panel
#define SENSOR_NUM_TEMP_FP										(0x79)

// Middle panel
#define SENSOR_NUM_TEMP_MP										(0x7A)

// OCP NIC card
#define SENSOR_NUM_TEMP_OCP0									(0x7B)
#define SENSOR_NUM_TEMP_OCP1									(0x7C)

// Riser card
#define SENSOR_NUM_TEMP_RISER0									(0x7D)

// NVMe




// #define SENSOR_NUM_									(0x)


#endif
