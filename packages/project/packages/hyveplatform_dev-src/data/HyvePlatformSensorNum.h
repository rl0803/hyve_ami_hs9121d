 /******************************************************************
 *
 * @file	HyvePlatformSensorNum.h
 * @brief	The definition of the Hyve platform sensor number 
 *
 ******************************************************************/

#ifndef HYVEPLATFORMSENSORNUM_H_
#define HYVEPLATFORMSENSORNUM_H_


#define BMC_SENSOR_LUN											(BMC_SENSOR_LUN00)

/********************* LUN 00 *********************/
// Event Only
#define SENSOR_NUM_CPU_CATERR									(0x00) // TODO
#define SENSOR_NUM_CPU0_PRESENT									(0x04) // TODO, can use the IO_P0_PRSNT_L_PLD_N
#define SENSOR_NUM_CPU0_PROCHOT									(0x08) // TODO
#define SENSOR_NUM_CPU0_VRHOT									(0x0C) // TODO
#define SENSOR_NUM_CPU0_THERMTRIP								(0x10)
#define SENSOR_NUM_CPU0_VCC_IN_ERR								(0x14) // TODO

#define SENSOR_NUM_SEL_STATUS									(0x21)
#define SENSOR_NUM_FRB2_TIMEOUT									(0x23)
#define SENSOR_NUM_BMC_RESET 									(0x24)
#define SENSOR_NUM_BMC_FW_CHANGE								(0x25)
#define SENSOR_NUM_SYSTEMEVENT									(0x30)
#define SENSOR_NUM_BUTTON_PRESS									(0x31)
#define SENSOR_NUM_ACPI_STATUS									(0x34)

#define SENSOR_NUM_CPU0_MEM_HOT									(0x40) // TODO
#define SENSOR_NUM_CPU0_MEM_VR_HOT								(0x44) // TODO
#define SENSOR_NUM_P0_MEM_THERMTRIP								(0x48) // TODO
#define SENSOR_NUM_POWER_UNIT									(0x50)	// AC Lost
#define SENSOR_NUM_INTRUSION_STATUS								(0x51)
#define SENSOR_NUM_BIOS_POST_CMPLT								(0x52)
#define SENSOR_NUM_PMBUS_ALERT									(0x53) // optional, choose not implement

// Threshold or Discrete

// CPU
#define SENSOR_NUM_CPU0_TEMP									(0x01) // From APML
#define SENSOR_NUM_CPU0_VDDSOC									(0x09) // ADC10
#define SENSOR_NUM_CPU0_VDDIO									(0x0D) // ADC9
#define SENSOR_NUM_CPU0_VDDCORE0								(0x11) // ADC11
#define SENSOR_NUM_CPU0_VDDCORE1								(0x12) // ADC12
#define SENSOR_NUM_CPU0_VDD1V1									(0x15) // ADC8
#define SENSOR_NUM_CPU0_VDD1V8									(0x16) // ADC6
#define SENSOR_NUM_CPU0_VDD3V3									(0x17) // ADC4
#define SENSOR_NUM_P0_PACKAGE_POWER								(0x19) // From APML

// MB Temp. Sensor
#define SENSOR_NUM_OUTLET_TEMP									(0x20) // THERMAL SENSOR 2, ADDR 0x94
#define SENSOR_NUM_INLET_TEMP									(0x21) // THERMAL SENSOR 1, ADDR 0x92

// VR
#define SENSOR_NUM_CPU0_VR0_TEMP								(0x23) // VDD_CORE_0_VDD_SOC
#define SENSOR_NUM_CPU0_VR1_TEMP								(0x24) // VDD_CORE_1_VDD_11
#define SENSOR_NUM_CPU0_VR2_TEMP								(0x25) // VDD_VDDIO
#define SENSOR_NUM_CPU0_VR0_POUT								(0x26)
#define SENSOR_NUM_CPU0_VR1_POUT								(0x27)
#define SENSOR_NUM_CPU0_VR2_POUT								(0x28)

// MB Voltage (ADC)
#define SENSOR_NUM_VOLT_P12V									(0x33) // ADC0
#define SENSOR_NUM_AUX_P12V										(0x34) // ADC13
#define SENSOR_NUM_AUX_P5V										(0x35) // ADC5
#define SENSOR_NUM_AUX_P3V3										(0x36) // ADC14

// DIMM
#define SENSOR_NUM_P0_DIMM_A0_TEMP								(0x40)
#define SENSOR_NUM_P0_DIMM_B0_TEMP								(0x41)
#define SENSOR_NUM_P0_DIMM_C0_TEMP								(0x42)
#define SENSOR_NUM_P0_DIMM_D0_TEMP								(0x43)
#define SENSOR_NUM_P0_DIMM_E0_TEMP								(0x44)
#define SENSOR_NUM_P0_DIMM_F0_TEMP								(0x45)
#define SENSOR_NUM_P0_DIMM_G0_TEMP								(0x46)
#define SENSOR_NUM_P0_DIMM_H0_TEMP								(0x47)
#define SENSOR_NUM_P0_DIMM_I0_TEMP								(0x48)
#define SENSOR_NUM_P0_DIMM_J0_TEMP								(0x49)
#define SENSOR_NUM_P0_DIMM_K0_TEMP								(0x4A)
#define SENSOR_NUM_P0_DIMM_L0_TEMP								(0x4B)

// PSU0
#define SENSOR_NUM_PSU0_TEMP									(0x80)
#define SENSOR_NUM_PSU0_VOUT									(0x84)
#define SENSOR_NUM_PSU0_CIN										(0x88)
#define SENSOR_NUM_PSU0_COUT									(0x8C)
#define SENSOR_NUM_PSU0_POUT									(0x90)
#define SENSOR_NUM_PSU0_FAN										(0x94)
#define SENSOR_NUM_PSU0_STATUS									(0x98)
#define SENSOR_NUM_PSU0_PIN										(0x9C)
// PSU1
#define SENSOR_NUM_PSU1_TEMP									(0x81)
#define SENSOR_NUM_PSU1_VOUT									(0x85)
#define SENSOR_NUM_PSU1_CIN										(0x89)
#define SENSOR_NUM_PSU1_COUT									(0x8D)
#define SENSOR_NUM_PSU1_POUT									(0x91)
#define SENSOR_NUM_PSU1_FAN										(0x95)
#define SENSOR_NUM_PSU1_STATUS									(0x99)
#define SENSOR_NUM_PSU1_PIN										(0x9D)

// GPU
#define SENSOR_NUM_GPU0_TEMP									(0xD9) // Reserved

// NIC card
#define SENSOR_NUM_NIC_CARD0_TEMP								(0xD8) // Reserved

// Front panel board
#define SENSOR_NUM_FP_TEMP										(0xE4)

// PDB
#define SENSOR_NUM_PDB0_TEMP									(0xC1)
#define SENSOR_NUM_PDB0_VOLT_P12V								(0xC3) // ADC1
#define SENSOR_NUM_PDB0_VOLT_P5V								(0xC5) // ADC3
#define SENSOR_NUM_PDB0_VOLT_P3V3								(0xC7) // ADC2

// Riser card
#define SENSOR_NUM_RISER0_TEMP									(0xC9) // Reserved

// RAID card
#define SENSOR_NUM_RAID_TEMP									(0xD0) // Reserved

// Fan
#define SENSOR_NUM_Fan0_0_TACH									(0xA0)
#define SENSOR_NUM_Fan0_1_TACH									(0xA1)
#define SENSOR_NUM_Fan1_0_TACH									(0xA2)
#define SENSOR_NUM_Fan1_1_TACH									(0xA3)
#define SENSOR_NUM_Fan2_0_TACH									(0xA4)
#define SENSOR_NUM_Fan2_1_TACH									(0xA5)
#define SENSOR_NUM_Fan3_0_TACH									(0xA6)
#define SENSOR_NUM_Fan3_1_TACH									(0xA7)

#define SENSOR_NUM_Fan4_0_TACH									(0xA8)
#define SENSOR_NUM_Fan4_1_TACH									(0xA9)
#define SENSOR_NUM_Fan5_0_TACH									(0xAA)
#define SENSOR_NUM_Fan5_1_TACH									(0xAB)
#define SENSOR_NUM_Fan6_0_TACH									(0xAC)
#define SENSOR_NUM_Fan6_1_TACH									(0xAD)
// Fan board
#define SENSOR_NUM_FANBOARD0_TEMP								(0xE0)

// Battery
#define SENSOR_NUM_BAT_VOLT_P3V									(0xCF) // ADC7



// #define SENSOR_NUM_									(0x)


#endif
