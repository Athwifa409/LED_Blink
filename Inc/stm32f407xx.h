/*
 * stm32f407xx.h
 *
 *  Created on: 02-Oct-2026
 *      Author: athwi
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_

#include <stddef.h>
#include <stdint.h>

#define __vo volatile

/*
 * Base address of Flash and SRAM memories
 */
#define FLASH_BASEADDR     0x08000000U
#define SRAM1_BASEADDR     0x20000000U
#define SRAM2_BASEADDR     0x2001C000U
#define ROM_BASEADDR       0x1FFF0000U
#define SRAM               SRAM1_BASEADDR    /* just gave a name for SRAM1_BASEADDR for easy access since we only use that here. */

/*
 * AHBx and APBx bus peripheral base addresses
 */
#define PERIPH_BASEADDR       0x40000000U
#define APB1PERIPH_BASEADDR   PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR   0x40010000U
#define AHB1PERIPH_BASEADDR   0x40020000U
#define AHB2PERIPH_BASEADDR   0x50000000U

/*
 * Base address of peripherals hanging on AHB1 bus
 */
#define GPIOA_BASEADDR    (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR    (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR    (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR    (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR    (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR    (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR    (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR    (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR    (AHB1PERIPH_BASEADDR + 0x2000)

#define RCC_BASEADDR        (AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASEADDR    (APB2PERIPH_BASEADDR + 0x3C00)

#define SPI1_BASEADDR    (APB2PERIPH_BASEADDR + 0x3000)

#define USART1_BASEADDR  (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR  (APB2PERIPH_BASEADDR + 0x1400)

#define SYSCFG_BASEADDR  (APB2PERIPH_BASEADDR + 0x3800)

/******************************************************************************************
 * Peripheral register definition structures
 *****************************************************************************************/

/*
 * Peripheral register definition structure for gpio
 */
typedef struct
{
	__vo uint32_t MODER;     /* GPIO port mode register.                        Address offset: 0x00 */
	__vo uint32_t OTYPER;    /* GPIO port output type register.                 Address offset: 0x04 */
	__vo uint32_t OSPEEDR;   /* GPIO port output speed register.                Address offset: 0x08 */
	__vo uint32_t PUPDR;     /* GPIO port pull-up/pull-down register.           Address offset: 0x0C */
	__vo uint32_t IDR;       /* GPIO port input data register.                  Address offset: 0x10 */
	__vo uint32_t ODR;       /* GPIO port output data register.                 Address offset: 0x14 */
	__vo uint32_t BSRR;      /* GPIO port bit set/reset register.               Address offset: 0x18 */
	__vo uint32_t LCKR;      /* GPIO port configuration lock register.          Address offset: 0x1C */
	__vo uint32_t AFR[2];    /* AFR[0] = GPIO alternate function low register.  Address offset: 0x20 */
	                         /* AFR[1] = GPIO alternate function high register. Address offset: 0x24 */

}GPIO_RegDef_t;

/*
 * Peripheral register definition structure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;     /* Interrupt mask register.               Address offset: 0x00 */
	__vo uint32_t EMR;     /* Event mask register.                   Address offset: 0x04 */
	__vo uint32_t RTSR;    /* Rising trigger selection register.     Address offset: 0x08 */
	__vo uint32_t FTSR;    /* Falling trigger selection register.    Address offset: 0x0C */
	__vo uint32_t SWIER;   /* Software interrupt event register.     Address offset: 0x10 */
	__vo uint32_t PR;      /* Pending register.                      Address offset: 0x14 */


}EXTI_RegDef_t;

/*
 * Peripheral register definition structure for SYSCNFG
 */
typedef struct{
	__vo uint32_t MEMRMP;         /* SYSCFG memory remap register.                        Address offset: 0x00 */
	__vo uint32_t PMC;            /* SYSCFG peripheral mode configuration register.       Address offset: 0x04 */
	__vo uint32_t EXTICR[4];      /* SYSCFG external interrupt configuration register 1.  Address offset: 0x08 - 0x14*/
	uint32_t      RESERVED1[2];   /* Reserved                                             Address: 0x18 - 0x1C */
	__vo uint32_t CMPCR;          /* Compensation cell control register.                  Address offset: 0x20 */
	uint32_t      RESERVED2[2];   /* Reserved                                             Address: 0x24 - 0x28 */
	__vo uint32_t CFGR;           /* SYSCFG configurarion register                        Address offset: 0x2C */

}SYSCFG_RegDef_t;

/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t CR;           /* RCC clock control register.                                    Address offset: 0x00 */
	__vo uint32_t PLLCFGR;      /* RCC PLL configuration register.                                Address offset: 0x04 */
	__vo uint32_t CFGR;         /* RCC clock configuration register.                              Address offset: 0x08 */
	__vo uint32_t CIR;          /* RCC clock interrupt register.                                  Address offset: 0x0C */
	__vo uint32_t AHBRSTR[3];   /* RCC AHB1 peripheral reset register.                            Address offset: 0x10
	                               RCC AHB2 peripheral reset register.                            Address offset: 0x14
	                               RCC AHB3 peripheral reset register.                            Address offset: 0x18 */
	uint32_t      RESERVED0;    /* Reserved, 0x1C                                                                      */
	__vo uint32_t APBRSTR[2];   /* RCC APB1 peripheral reset register.                            Address offset: 0x20
	                               RCC APB2 peripheral reset register.                            Address offset: 0x24 */
	uint32_t      RESERVED1[2]; /* Reserved, 0x28 - 0x2C                                                               */
	__vo uint32_t AHBENR[3];    /* RCC AHB1 peripheral clock enable register.                     Address offset: 0x30
	                               RCC AHB2 peripheral clock enable register.                     Address offset: 0x34
	                               RCC AHB3 peripheral clock enable register.                     Address offset: 0x38 */
	uint32_t      RESERVED2;    /* Reserved, 0x3C                                                                      */
	__vo uint32_t APBENR[2];    /* RCC APB1 peripheral clock enable register.                     Address offset: 0x40
	                               RCC APB2 peripheral clock enable register.                     Address offset: 0x44 */
	uint32_t      RESERVED3[2]; /* Reserved, 0x48, 0x4C                                                                */
	__vo uint32_t AHBLPENR[3];  /* RCC AHB1 peripheral clock enable in low power mode register.   Address offset: 0x50
	                               RCC AHB2 peripheral clock enable in low power mode register.   Address offset: 0x54
	                               RCC AHB3 peripheral clock enable in low power mode register.   Address offset: 0x58 */
	uint32_t      RESERVED4;    /* Reserved, 0x5C                                                                      */
	__vo uint32_t APBLPENR[2];  /* RCC APB1 peripheral clock enable in low power mode register.   Address offset: 0x60
	                               RCC APB2 peripheral clock enabled in low power mode register.  Address offset: 0x64 */
	uint32_t      RESERVED5[2]; /* Reserved, 0x68, 0x6C                                                                */
	__vo uint32_t BDCR;         /* RCC Backup domain control register.                            Address offset: 0x70 */
	__vo uint32_t CSR;          /* RCC clock control & status register.                           Address offset: 0x74 */
	uint32_t      RESERVED6[2]; /* Reserved, 0x78, 0x7C                                                                */
	__vo uint32_t SSCGR;        /* RCC spread spectrum clock generation register.                 Address offset: 0x80 */
	__vo uint32_t PLLI2SCFGR;   /* RCC PLLI2S configuration register.                             Address offset: 0x84 */

}RCC_RegDef_t;



/****************************************************************************
 * macros
 ********************************************************************************/

/*
 * Initialising register structures of GPIOs for future use
 */
#define GPIOA    ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB    ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC    ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD    ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE    ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF    ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG    ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH    ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI    ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC              ((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI              ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG              ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock enable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 0))
#define GPIOB_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 1))
#define GPIOC_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 2))
#define GPIOD_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 3))
#define GPIOE_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 4))
#define GPIOF_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 5))
#define GPIOG_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 6))
#define GPIOH_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 7))
#define GPIOI_PCLK_EN()     (RCC -> AHBENR[0] |= (1 << 8))

/*
 * Clock enable macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_EN()     (RCC -> APBENR[1] |= (1 << 14))

/*
 * Clock disable macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 0))
#define GPIOB_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 1))
#define GPIOC_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 2))
#define GPIOD_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 3))
#define GPIOE_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 4))
#define GPIOF_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 5))
#define GPIOG_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 6))
#define GPIOH_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 7))
#define GPIOI_PCLK_DI()     (RCC -> AHBENR[0] &= ~(0 << 8))

/*
 * Clock DISable macros for SYSCFG peripherals
 */

#define SYSCFG_PCLK_DI()     (RCC -> APBENR[1] &= ~(0 << 14))

/*
 * MACROS TO RESET THE GPIOx peripherals
 */
#define GPIOA_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 0)); (RCC -> AHBRSTR[0] &= ~(1 << 0)); } while(0)
#define GPIOB_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 1)); (RCC -> AHBRSTR[0] &= ~(1 << 1)); } while(0)
#define GPIOC_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 2)); (RCC -> AHBRSTR[0] &= ~(1 << 2)); } while(0)
#define GPIOD_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 3)); (RCC -> AHBRSTR[0] &= ~(1 << 3)); } while(0)
#define GPIOE_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 4)); (RCC -> AHBRSTR[0] &= ~(1 << 4)); } while(0)
#define GPIOF_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 5)); (RCC -> AHBRSTR[0] &= ~(1 << 5)); } while(0)
#define GPIOG_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 6)); (RCC -> AHBRSTR[0] &= ~(1 << 6)); } while(0)
#define GPIOH_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 7)); (RCC -> AHBRSTR[0] &= ~(1 << 7)); } while(0)
#define GPIOI_REG_RESET()      do{ (RCC -> AHBRSTR[0] |= (1 << 8)); (RCC -> AHBRSTR[0] &= ~(1 << 8)); } while(0)



/*
 * Return port for a given GPIOx base address
 */
#define GPIO_BASEADDR_TO_CODE(x) ((x == GPIOA)? 0 :\
		                          (x == GPIOB)? 1 :\
		                          (x == GPIOC)? 2 :\
		                          (x == GPIOD)? 3 :\
				                  (x == GPIOE)? 4 :\
				                  (x == GPIOF)? 5 :\
						          (x == GPIOG)? 6 :\
								  (x == GPIOH)? 7 :\
								  (x == GPIOI)? 8 : 0 )


/*
 *Some generic macros
 */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        ENABLE
#define GPIO_PIN_RESET      DISABLE


#include "stm32f407_gpio.h"





#endif /* STM32F407XX_H_ */
