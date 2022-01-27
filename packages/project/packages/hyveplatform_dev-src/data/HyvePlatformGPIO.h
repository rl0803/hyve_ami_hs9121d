 /******************************************************************
 *
 * @file	HyvePlatformGPIO.h
 * @brief	The platform GPIO pin mapping
 *
 ******************************************************************/

#ifndef HYVEPLATFORMGPIO_H_
#define HYVEPLATFORMGPIO_H_

#include "HyveGPIOMap.h"


/********************* Platform GPIO Pin Definition *********************/
/*
	Ref: HS9121D_X00_BMC GPIO_HW strap table_20211229
	
	Note:
	    Remember to search "TODO" for what must need to check with EE/CPLD team

*/

#define IO_RGMII_BMC_R_MDC                  GPIOA0
#define IO_RGMII_BMC_R_MDIO                 GPIOA1
#define IO_SMB_BMC_FAN_HWM_SCL              GPIOA2 // I2C-12
#define IO_SMB_BMC_FAN_HWM_SDA              GPIOA3
#define IO_SMB_BMC_FANBD_SCL                GPIOA4 // I2C-13
#define IO_SMB_BMC_FANBD_SDA                GPIOA5
#define IO_SMB_BMC_PLD_SCL                  GPIOA6 // I2C-14, reserved for debug card
#define IO_SMB_BMC_PLD_SDA                  GPIOA7

#define IO_PCIE_P2_MCIO1_ALERT_N            GPIOB0 // GPIO, Input, From J31-E1.S
#define IO_PCIE_P3_MCIO2_ALERT_N            GPIOB1 // GPIO, Input, From J32-E1.S
#define IO_XGMI_G2_AIC1_ALERT_N             GPIOB2 // GPIO, Input, From J33-PCIe card
#define IO_XGMI_G3_AIC2_ALERT_N             GPIOB3 // GPIO, Input, From J34-PCIe card
#define IO_P0_CORETYPE_0                    GPIOB4 // GPIO, Input
#define IO_P0_CORETYPE_1                    GPIOB5 // GPIO, Input
#define IO_P0_CORETYPE_2                    GPIOB6 // GPIO, Input
#define IO_NC_GPIOB7                        GPIOB7 // No Use

#define IO_RGMII_BMC_R_TX_CLK               GPIOC0
#define IO_RGMII_BMC_R_TX_CTRL              GPIOC1
#define IO_RGMII_BMC_R_TXD0                 GPIOC2
#define IO_RGMII_BMC_R_TXD1                 GPIOC3
#define IO_RGMII_BMC_R_TXD2                 GPIOC4
#define IO_RGMII_BMC_R_TXD3                 GPIOC5
#define IO_RGMII_BMC_RX_CLK                 GPIOC6
#define IO_RGMII_BMC_RX_CTRL                GPIOC7

#define IO_RGMII_BMC_RXD0                   GPIOD0
#define IO_RGMII_BMC_RXD1                   GPIOD1
#define IO_RGMII_BMC_RXD2                   GPIOD2
#define IO_RGMII_BMC_RXD3                   GPIOD3
#define IO_RGMII4TXCK                       GPIOD4
#define IO_NCSI_BMC_TX_EN                   GPIOD5
#define IO_NCSI_BMC_TXD_0                   GPIOD6
#define IO_NCSI_BMC_TXD_1                   GPIOD7

#define IO_FM_BACKUP_BIOS_SEL_N             GPIOE0 // GPIO, Output, High: primary BIOS; Low: secondary BIOS
#define IO_FM_BIOS_BMC_CTRL                 GPIOE1 // GPIO, Output, pull High to enable BIOS flash access
#define IO_CLK_50M_CKMNG_BMCB               GPIOE2
#define IO_RGMII4_CTL                       GPIOE3
#define IO_NCSI_BMC_RXD_0                   GPIOE4
#define IO_NCSI_BMC_RXD_1                   GPIOE5
#define IO_NCSI_BMC_CRS_DV                  GPIOE6
#define IO_RMII4_RXER                       GPIOE7

#define IO_PWRGD_SYS_PWROK_BMC              GPIOF0 // GPIO, Input, system power good
#define IO_PWRGD_PS_PWROK_BMC               GPIOF1 // GPIO, Input, power supply power good
#define IO_FM_SRST_REQ2_N                   GPIOF2 // GPIO, Output, to request ROT do BMC reset
#define IO_FM_BMC_RESET_DET_N               GPIOF3 // GPIO, Output, to trigger ROT do BMC FW auth
#define IO_TP_GPIOF4                        GPIOF4 // GPIO, Input, reserved
#define IO_TP_GPIOF5                        GPIOF5 // GPIO, Input, reserved
#define IO_BMC_CPLD_JTAG_MUX_SEL            GPIOF6 // GPIO, Output, High: Riser; Low: CPLD
#define IO_FM_PWRBRK_BMC_N                  GPIOF7 // GPIO, Output, to request CPLD do power break(PCIe device throttle)

#define IO_BMC_OCP1_SMRST_L                 GPIOG0 // GPIO, Output, default pull High, to reset OCP??
#define IO_FM_DP_CONN_PWR_EN_CTL            GPIOG1 // GPIO, Output, default pull Low, power enable for Display Port Connector
#define IO_FP_ID_LED_N                      GPIOG2 // GPIO, Output
#define IO_FM_P0_CPLD_THERMTRIP_N           GPIOG3 // GPIO, Input, CPU thermal trip signal
#define IO_NC_GPIOG4                        GPIOG4 // No Use
#define IO_NC_GPIOG5                        GPIOG5 // No Use
#define IO_NC_GPIOG6                        GPIOG6 // No Use
#define IO_NC_GPIOG7                        GPIOG7 // No Use

#define IO_SGPIO_BMC_CPLD_CLK               GPIOH0
#define IO_SGPIO_BMC_CPLD_LD                GPIOH1
#define IO_SGPIO_BMC_CPLD_OUT               GPIOH2
#define IO_SGPIO_BMC_CPLD_IN                GPIOH3
#define IO_SMB_BMC_CPLD_REMOTE_SCL          GPIOH4 // I2C-15
#define IO_SMB_BMC_CPLD_REMOTE_SDA          GPIOH5
#define IO_SMB_ROT_BMC_SCL                  GPIOH6 // I2C-16
#define IO_SMB_ROT_BMC_SDA                  GPIOH7

#define IO_BMC_JTAGM2_NTRST                 GPIOI0
#define IO_BMC_HDT_TDO                      GPIOI1
#define IO_BMC_HDT_TCK                      GPIOI2
#define IO_BMC_HDT_TMS                      GPIOI3
#define IO_BMC_HDT_TDI                      GPIOI4
#define IO_FP_ID_BTN_N                      GPIOI5 // GPIO, Input
#define IO_BMC_CPLD_JTAG_MUX_OE             GPIOI6 // GPIO, Output, to enable the JTAG MUX, High: disable; Low: enable
#define IO_CLK_100M_9DML0455_CLKIN_LOS_N    GPIOI7 // GPIO, Input, CLK_100M_9DML0455_CLKIN_LOS_N, to inform the BMC PCIe clock generator loss

#define IO_RST_RSMRST_BMC_N                 GPIOJ0 // GPIO, Input, from CPLD
#define IO_P0_BMC_APML_ALERT_L              GPIOJ1 // GPIO, Input, AMD APML Alert, Active Low
#define IO_BMC_I3C4_I2C_SCL                 GPIOJ2 // APML, I3C-4 or I2C-2
#define IO_BMC_I3C4_I2C_SDA                 GPIOJ3
#define IO_P0_NMI_SYNC_FLOOD_L              GPIOJ4 // GPIO, Output, default pull High, basically no use
#define IO_P0_SPD_HOST_CTRL_L               GPIOJ5 // GPIO, Input, Low: to inform the BMC the owner-ship of DIMMs is CPU
#define IO_EMMC_RST_N                       GPIOJ6 // GPIO, Output, to reset EMMC, this pin is reserved. currently use IO_FM_BMC_EMMC_RST_N instead
#define IO_P0_SMERR_L                       GPIOJ7 // GPIO, Input, CPU SM error

#define IO_SMB_PSU_STBY_LVC3_SCL            GPIOK0 // I2C-5, PMBUS
#define IO_SMB_PSU_STBY_LVC3_SDA            GPIOK1
#define IO_SMB_BMC_G_MCIO_SCL               GPIOK2 // I2C-6, SMBus for PCIe device access
#define IO_SMB_BMC_G_MCIO_SDA               GPIOK3
#define IO_SMB_BMC_CLKBUF_GEN_SCL           GPIOK4 // I2C-7, though the BMC can access the Clock-Gen IC but it doesn't control it.
#define IO_SMB_BMC_CLKBUF_GEN_SDA           GPIOK5
#define IO_SMB_TEMP_FRU_SCL                 GPIOK6 // I2C-8
#define IO_SMB_TEMP_FRU_SDA                 GPIOK7

#define IO_SMB_BMC_P0_VR_SCL                GPIOL0 // I2C-9
#define IO_SMB_BMC_P0_VR_SDA                GPIOL1
#define IO_SMB_BMC_OCP_RISER_SCL            GPIOL2 // I2C-10
#define IO_SMB_BMC_OCP_RISER_SDA            GPIOL3
#define IO_P5V_AUX_RST_DLY                  GPIOL4 // GPIO, Output, to reset standby 5V, High: enable delay reset IC input control
#define IO_P3V3_AUX_RST_DLY                 GPIOL5 // GPIO, Output, to reset standby 3.3V, High: enable delay reset IC input control
#define IO_NC_GPIOL6                        GPIOL6 // No Use
#define IO_NC_GPIOL7                        GPIOL7 // No Use

#define IO_FM_BMC_ONCTL_N                   GPIOM0 // GPIO, Output, to inform CPLD that the BMC is ready
#define IO_P0_PWRGD                         GPIOM1 // GPIO, Input, the CPU power good
#define IO_PLTRST_BMC_IN_N                  GPIOM2 // GPIO, Input, reserved, TODO: check with CPLD
#define IO_NC_GPIOM3                        GPIOM3 // No Use
#define IO_NC_GPIOM4                        GPIOM4 // No Use
#define IO_NC_GPIOM5                        GPIOM5 // No Use
#define IO_BMC_UART_1_TXD                   GPIOM6 // For SOL
#define IO_BMC_UART_1_RXD                   GPIOM7

#define IO_P0_PROCHOT_N                     GPION0 // GPIO, Input
#define IO_NC_GPION1                        GPION1 // No Use
#define IO_BMC_PLD_VR_ALERT_L               GPION2 // GPIO, Output, to inform the CPLD
#define IO_NC_GPION3                        GPION3 // No Use
#define IO_EC_BMC_AP1_RESET_N               GPION4 // GPIO, Input, the ROT informs the BMC
#define IO_EC_BMC_FATAL_ERROR_N             GPION5 // GPIO, Input, the ROT informs the BMC
#define IO_FM_CEC_BIOS_RESET_IN             GPION6 // GPIO, Output, to inform the ROT to do the BIOS FW auth
#define IO_NC_GPION7                        GPION7 // No Use

/* Note:
	By HW design, the EC_BMC_AP1_RESET_N and the EC_BMC_FATAL_ERROR_N pin are also passed to the CPLD
	then the CPLD 'OR' theses 2 signal and inform the BMC by FM_CEC_BIOS_AUTH_COMP pin
	So the BMC only need to care the FM_CEC_BIOS_AUTH_COMP pin and can ignore the EC_BMC_AP1_RESET_N and the EC_BMC_FATAL_ERROR_N pin
*/

#define IO_NC_GPIOO0                        GPIOO0 // No Use
#define IO_NC_GPIOO1                        GPIOO1 // No Use
#define IO_NC_GPIOO2                        GPIOO2 // No Use
#define IO_NC_GPIOO3                        GPIOO3 // No Use
#define IO_NC_GPIOO4                        GPIOO4 // No Use
#define IO_NC_GPIOO5                        GPIOO5 // No Use
#define IO_FM_AUTH_COMPLETE_N               GPIOO6 // GPIO, Output, to inform the CPLD that FW auth is done and is good to go next stage
#define IO_FAN_DIRECTION                    GPIOO7 // GPIO, Input, TODO: the direction has not determined yet

#define IO_FM_BMC_PWRBTN_IN_N               GPIOP0 // GPIO, Input
#define IO_FM_BMC_PWRBTN_OUT_N              GPIOP1 // GPIO, Output, pass the button signal to the CPLD
#define IO_RST_SYSTEM_BTN_IN_N              GPIOP2 // GPIO, Input
#define IO_RST_SYSRST_BTN_OUT_N             GPIOP3 // GPIO, Output, pass the button signal to the CPLD
#define IO_NC_GPIOP4                        GPIOP4 // No Use
#define IO_NC_GPIOP5                        GPIOP5 // No Use
#define IO_NC_GPIOP6                        GPIOP6 // No Use
#define IO_BMC_HW_HEARTBEAT_N               GPIOP7 // GPIO, Output

#define IO_RESERVED_GPIOQ0                  GPIOQ0 // Reserved
#define IO_RESERVED_GPIOQ1                  GPIOQ1 // Reserved
#define IO_RESERVED_GPIOQ2                  GPIOQ2 // Reserved
#define IO_RESERVED_GPIOQ3                  GPIOQ3 // Reserved
#define IO_RESERVED_GPIOQ4                  GPIOQ4 // Reserved
#define IO_RESERVED_GPIOQ5                  GPIOQ5 // Reserved
#define IO_RESERVED_GPIOQ6                  GPIOQ6 // Reserved
#define IO_RESERVED_GPIOQ7                  GPIOQ7 // Reserved

#define IO_NC_GPIOR0                        GPIOR0 // No Use
#define IO_NC_GPIOR1                        GPIOR1 // No Use
#define IO_NC_GPIOR2                        GPIOR2 // No Use
#define IO_NC_GPIOR3                        GPIOR3 // No Use
#define IO_NC_GPIOR4                        GPIOR4 // No Use
#define IO_NC_GPIOR5                        GPIOR5 // No Use
#define IO_NC_GPIOR6                        GPIOR6 // No Use
#define IO_NC_GPIOR7                        GPIOR7 // No Use

#define IO_RST_RGMII_PHYRST_N               GPIOS0 // GPIO, Output, to reset the phy-IC, HW default sets it NI
#define IO_FM_BMC_PLD_RESERVED              GPIOS1 // GPIO, Output, to the CPLD, reserved
#define IO_RST_RTCRST_N                     GPIOS2 // GPIO, Output, this pin can both reset the CMOS and the BMC RTC
#define IO_P0_HDT_SEL_0                     GPIOS3 // GPIO, Output, HDT source selection, High (default): CPU HDT; Low: BMC HDT
#define IO_FM_BIOS_FLASH_SEL0_N             GPIOS4 // GPIO, Input, from the ROT to know which BIOS it is accessing
#define IO_FM_BIOS_FLASH_SEL1_N             GPIOS5 // GPIO, Input, from the ROT to know which BIOS it is accessing
#define IO_PCIE_P1_RISER_ALERT_N            GPIOS6 // GPIO, Input, SMBus Alert from the Riser Card
#define IO_TEMP_I2C_ALERT_L                 GPIOS7 // GPIO, Input, Alert from thermal sensors, need to send I2C cmd to check which one sent

#define IO_P12V_STBY_SCALED                 GPIOT0 // ADC-0, Standby 12V
#define IO_P12V_SCALED                      GPIOT1 // ADC-1, power distribution board 12V
#define IO_P3V3_SCALED                      GPIOT2 // ADC-2, power distribution board 3.3V
#define IO_P3V3_STBY_SCALED                 GPIOT3 // ADC-3, Standby 3.3V
#define IO_P0_VDD_33_DUAL_SCALED            GPIOT4 // ADC-4, CPU VDD 3.3V
#define IO_P5V_AUX_SCALED                   GPIOT5 // ADC-5, AUX 5V
#define IO_P0_VDD_18_DUAL_SCALED            GPIOT6 // ADC-6, CPU VDD 1.8V
#define IO_A_P3V_BAT_SCALED                 GPIOT7 // ADC-7, 3.3V battery

#define IO_P0_VDD_11_SUS_SCALED             GPIOU0 // ADC-8, CPU VDD 1.1V
#define IO_P0_VDD_VDDIO_RUN_SCALED          GPIOU1 // ADC-9, CPU VDDIO 
#define IO_P0_VDD_SOC_RUN_SCALED            GPIOU2 // ADC-10, CPU VDDCR_SOC
#define IO_P0_VDD_CORE_0_SCALED             GPIOU3 // ADC-11, CPU VDDCR_CPU0
#define IO_P0_VDD_CORE_1_SCALED             GPIOU4 // ADC-12, CPU VDDCR_CPU1
#define IO_P12V_AUX_SCALED                  GPIOU5 // ADC-13, AUX 12V
#define IO_P3V3_AUX_SCALED                  GPIOU6 // ADC-14, AUX 3V3 , Note: currently EE doesn't implement the circuit
#define IO_NC_GPIOU7                        GPIOU7 // No Use

#define IO_PLD_BMC_SLP_S3_L                 GPIOV0 // GPIO, Input, the CPLD informs the CPU S3 state to the BMC
#define IO_PLD_BMC_SLP_S5_L                 GPIOV1 // GPIO, Input, the CPLD informs the CPU S5 state to the BMC
#define IO_SPD_REMOTE_SEL                   GPIOV2 // GPIO, Output, to control the I3C mux for DIMMs access, but HW default sets it NI. High: enable; Low: disable
#define IO_NC_GPIOV3                        GPIOV3 // No Use
#define IO_A_P3V_BAT_SCALED_EN              GPIOV4 // GPIO, Output, High: to enable the mosfet that ADC 'P3V_BAT' can be available; default should keep Low to avoid the bat drained out
#define IO_BMC_HDT_DBREQ_L                  GPIOV5 // GPIO, Output
#define IO_IRQ_SMB_ROT_ALRT_N               GPIOV6 // GPIO, Output, to inform the ROT that SMBus (I2C-16 SMB_ROT_BMC) error occurs
#define IO_PSU_SMB_ALERT_N                  GPIOV7 // GPIO, Input, the PMBus Alert

#define IO_P0_BMC_ESPI1_D0                  GPIOW0
#define IO_P0_BMC_ESPI1_D1                  GPIOW1
#define IO_P0_BMC_ESPI1_D2                  GPIOW2
#define IO_P0_BMC_ESPI1_D3                  GPIOW3
#define IO_P0_BMC_ESPI_CLK1                 GPIOW4
#define IO_P0_BMC_ESPI_CS0_N                GPIOW5
#define IO_P0_BMC_ESPI_ALERT_N              GPIOW6
#define IO_P0_BMC_ESPI_RSOUT_N              GPIOW7

#define IO_NC_GPIOX0                        GPIOX0 // No Use
#define IO_BMC_SYS_STATUS_LED_CTRL_Y        GPIOX1 // GPIO, Output, Yellow LED
#define IO_BMC_SYS_STATUS_LED_CTRL_G        GPIOX2 // GPIO, Output, Green LED
#define IO_BMC_CLKGEN_I2CMUX_RST_N          GPIOX3 // GPIO, Output, BMC_CLKGEN_I2CMUX_RST_N, the reset pin for MUX-PCA9546
#define IO_BMC_PLINK_I2CMUX_RST_N           GPIOX4 // GPIO, Output, BMC_PLINK_I2CMUX_RST_N,  the reset pin for MUX-PCA9548
#define IO_BMC_GLINK_I2CMUX_RST_N           GPIOX5 // GPIO, Output, BMC_GLINK_I2CMUX_RST_N,  the reset pin for MUX-PCA9546
#define IO_NC_GPIOX6                        GPIOX6 // No Use
#define IO_NC_GPIOX7                        GPIOX7 // No Use

#define IO_FM_SRST_REQ1_N                   GPIOY0 // GPIO, Output, send the BMC reset event to the ROT, kind of like IO_FM_ROT_WDRST2_N
#define IO_FM_ROT_WDRST2_N                  GPIOY1 // Output, if enable WDT2, send the WDT reset event signal to the ROT
#define IO_P0_SMBUS_ALERT                   GPIOY2 // GPIO, Input, CPU SMBus Alert
#define IO_FM_BMC_EMMC_RST_N                GPIOY3 // GPIO, Output, to reset the EMMC, Note: the volt of this signal pin will be converted to 1.8V
#define IO_SPI_BMC_BOOT_IO2                 GPIOY4
#define IO_SPI_BMC_BOOT_IO3                 GPIOY5
#define IO_PU_SPI_BMC_BOOT_ABR              GPIOY6
#define IO_PU_SPI_BMC_BOOT_WP_N             GPIOY7

#define IO_NC_GPIOZ0                        GPIOZ0 // No Use
#define IO_BMC_SYS_STATUS_LED_CTRL_R        GPIOZ1 // GPIO, Output, Red LED, TODO: need to check this pin can drive High with external Pull-Down 2K R
#define IO_PU_SPI1WP_N                      GPIOZ2
#define IO_PU_GPIOZ3_SPI1_CLK               GPIOZ3
#define IO_PU_GPIOZ4_SPI1_MOSI              GPIOZ4
#define IO_PU_GPIOZ5_SPI1_MISO              GPIOZ5
#define IO_PU_GPIOZ6_SPI1_D2                GPIOZ6
#define IO_PU_GPIOZ7_SPI1_D3                GPIOZ7

#define IO_FM_REV_BOARD_ID0                 GPIO18A0 // GPIO, Input
#define IO_FM_REV_BOARD_ID1                 GPIO18A1 // GPIO, Input
#define IO_FM_REV_BOARD_ID2                 GPIO18A2 // GPIO, Input
#define IO_RESERVED_GPIO18A3                GPIO18A3 // Reserved
#define IO_RESERVED_GPIO18A4                GPIO18A4 // Reserved
#define IO_RESERVED_GPIO18A5                GPIO18A5 // Reserved
#define IO_RESERVED_GPIO18A6                GPIO18A6 // Reserved
#define IO_FM_CEC_BIOS_AUTH_COMP            GPIO18A7 // GPIO, Input, ROT informs the BMC that BIOS FW auth completed

#define IO_FM_PLD_BMC_RESERVED              GPIO18B0 /// GPIO, Input, Reserved
#define IO_RESERVED_GPIO18B1                GPIO18B1 // Reserved
#define IO_RESERVED_GPIO18B2                GPIO18B2 // Reserved
#define IO_RESERVED_GPIO18B3                GPIO18B3 // Reserved
#define IO_FM_BMC_BOARD_SKU_ID0_N           GPIO18B4 // GPIO, Input
#define IO_FM_BMC_BOARD_SKU_ID1_N           GPIO18B5 // GPIO, Input
#define IO_FM_BMC_BOARD_SKU_ID2_N           GPIO18B6 // GPIO, Input
#define IO_FM_BMC_BOARD_SKU_ID3_N           GPIO18B7 // GPIO, Input

#define IO_RESERVED_GPIO18C0                GPIO18C0 // Reserved
#define IO_RESERVED_GPIO18C1                GPIO18C1 // Reserved
#define IO_RESERVED_GPIO18C2                GPIO18C2 // Reserved
#define IO_RESERVED_GPIO18C3                GPIO18C3 // Reserved
#define IO_RESERVED_GPIO18C4                GPIO18C4 // Reserved
#define IO_RESERVED_GPIO18C5                GPIO18C5 // Reserved
#define IO_RESERVED_GPIO18C6                GPIO18C6 // Reserved
#define IO_RESERVED_GPIO18C7                GPIO18C7 // Reserved

#define IO_EMMC_CLK                         GPIO18D0
#define IO_EMMC_CMD                         GPIO18D1
#define IO_EMMC_DATA_0                      GPIO18D2
#define IO_EMMC_DATA_1                      GPIO18D3
#define IO_EMMC_DATA_2                      GPIO18D4
#define IO_EMMC_DATA_3                      GPIO18D5
#define IO_EMMC_CD_N                        GPIO18D6
#define IO_EMMC_WP_N                        GPIO18D7

#define IO_EMMC_DATA_4                      GPIO18E0
#define IO_EMMC_DATA_5                      GPIO18E1
#define IO_EMMC_DATA_6                      GPIO18E2
#define IO_EMMC_DATA_7                      GPIO18E3

#endif
