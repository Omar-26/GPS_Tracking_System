#include "mcu_hw.h"

uint8 au8_RCG_INDEX[NO_OF_GATES_FOR_PHERIPHERALS]={               /*Gate_Peripheral_WD*/Gate_Peripheral_WD
                                                                  ,/*Gate_Peripheral_TIMER*/Gate_Peripheral_TIMER
                                                                  ,/*Gate_Peripheral_GPIO*/Gate_Peripheral_GPIO
                                                                  ,/*Gate_Peripheral_DMA*/Gate_Peripheral_DMA
                                                                  ,/*Gate_Peripheral_HIB*/Gate_Peripheral_HIB
                                                                  ,/*Gate_Peripheral_UART*/Gate_Peripheral_UART
                                                                  ,/*Gate_Peripheral_SSI*/Gate_Peripheral_SSI
                                                                  ,/*Gate_Peripheral_I2C*/Gate_Peripheral_I2C
                                                                  ,/*Gate_Peripheral_USB*/Gate_Peripheral_USB
                                                                  ,/*Gate_Peripheral_CAN*/Gate_Peripheral_CAN
                                                                  ,/*Gate_Peripheral_ADC*/Gate_Peripheral_ADC
                                                                  ,/*Gate_Peripheral_ACMP*/Gate_Peripheral_ACMP
                                                                  ,/*Gate_Peripheral_PWM*/Gate_Peripheral_PWM
                                                                  ,/*Gate_Peripheral_QEI*/Gate_Peripheral_QEI
                                                                  ,/*Gate_Peripheral_EEPROM*/Gate_Peripheral_EEPROM
                                                                  ,/*Gate_Peripheral_WTIMER*/Gate_Peripheral_WTIMER
                                                                 };

volatile PORT_RegType* Array_of_pntr_to_GPIO_APB_GPI0_APB_BaseAddrArr[MAX_NUM_OF_PORTS] = {PORTA_APB_BaseAddr,PORTB_APB_BaseAddr,
                                                                                           PORTC_APB_BaseAddr,PORTD_APB_BaseAddr,
                                                                                           PORTE_APB_BaseAddr,PORTF_APB_BaseAddr};
