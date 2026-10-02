/*
 * stm32f407_gpio.c
 *
 *  Created on: 02-Oct-2026
 *      Author: athwi
 */

#include "stm32f407_gpio.h"

/*************************************************************************************************
 * APIs and their meanings
 *************************************************************************************************/

/***************************************************************************************************************************
 * @Function - GPIO_Init
 * @Brief    - This function initializes the GPIO peripheral in use
 * @Param1   - GPIO Handler function/address
 * @Param2   -
 * @Param3   -
 * @Return   - None
 * @Note     - None
 **********************************************************************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;   //temporary register

	//enable peripheral clock
	GPIO_PeriClkControl(pGPIOHandle ->pGPIOx , ENABLE);

	//1. Configure the mode of GPIO pin
	if(pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//NON INTERRUPT MODES
		temp = (pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode <<(2* pGPIOHandle ->pGPIO_PinConfig->GPIO_PinNumber));   //moder uses 2 bits so 2 * pinNumber.for PD12 moder[25:24]. temp = 01
		pGPIOHandle ->pGPIOx ->MODER &= ~(0x3 << (2 * pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber));  //clearing old modes. clearing [25:24]
		pGPIOHandle ->pGPIOx ->MODER |= temp;  //PD12 = 01. 01 is output mode(we gave like this in a macro)
		temp = 0;

	}else
	{
		if(pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure the FTSR
			EXTI ->FTSR |= (1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);  //enabling falling edge
			// Clear the RTSR bit
			EXTI ->RTSR &= ~(1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);  //disabling rising edge

		}else if(pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. Configure the RTSR
			EXTI ->RTSR |= (1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);
			// Clear the FTSR bit
			EXTI ->FTSR &= ~(1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);

		}else if(pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// Configure both FTSR and RTSR
			EXTI ->FTSR |= (1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);   //both falling and rising edge enabled
			EXTI ->RTSR |= (1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);

		}

		//2. Configure the GPIO Port selector in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber /4;   //pin = 12; 12/4 = 3
		uint8_t temp2 = pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber %4;   // 12 % 4 = 0
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle ->pGPIOx);      //GPIOD returns value 3
		SYSCFG_PCLK_EN();
		SYSCFG ->EXTICR[temp1] = portCode << (temp2 * 4);  //EXTICR[3] = 3 << 0 = 12th line connected to GPIO port D

		//3. Configure the EXTI interrupt delivery using IMR
		EXTI ->IMR |= (1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);  //This enable interrupt delivery for that EXTI line
	}

	temp = 0;

	//2. Configure the speed
	temp = (pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinSpeed << (2 * pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber));  //2* because it uses 2 bits per pin
	pGPIOHandle ->pGPIOx ->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber));  //ospeeder[25:24]
	pGPIOHandle ->pGPIOx ->OSPEEDR |= temp;  //we can wrie the speed. eg: GPIO_SPEED_FAST = 2(10) on the 2 bits

	temp = 0;

	//3. Configure the PUPD settings
	temp = (pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinPuPdControl << (2 * pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber));
	pGPIOHandle ->pGPIOx ->PUPDR &= ~(0x3 << (2 * pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber));
	pGPIOHandle ->pGPIOx ->PUPDR |= temp; //also uses 2 bit. eg: GPIO_NO_PUPD = 0(00)

	temp = 0;

	//4. Configure the Output type
	temp = (pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinOutputType << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);
	pGPIOHandle ->pGPIOx ->OTYPER &= ~(0x1 << pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber);
	pGPIOHandle ->pGPIOx ->OTYPER |= temp;

	temp = 0;

	//5. Configure the alternate functionality
	if(pGPIOHandle ->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		//Configure the alternate functionality register
		uint8_t temp1, temp2;
		temp1 = pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber / 8;  //AFR[0] = 0-7, AFR[1] = 8-15. for pin 12, 12/8 = 1. ie, AFR[1]
		temp2 = pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinNumber % 8;  // for pin 12, 12%8 = 4. ie, from pin8 to 12, need to move 4 bits
		pGPIOHandle ->pGPIOx ->AFR[temp1] &= ~(0xF << (4 * temp2));  // clearing the 12th bit
		pGPIOHandle ->pGPIOx ->AFR[temp1] |= (pGPIOHandle ->pGPIO_PinConfig ->GPIO_PinAltFunMode << (4 * temp2));  //moving 4 bits, to get the right pin

	}

}

/***************************************************************************************************************************
 * @Function - GPIO_DeInit
 * @Brief    - This function deinitializes the GPIO pin. Deinitialization means returns it to its reset state.
 * @Param1   - GPIO base address
 * @Param2   -
 * @Param3   -
 * @Return   - None
 * @Note     - None
 **********************************************************************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();             //reset macro do : rcc -> ahbrsts[0] |= (1 << 3)
	}else if(pGPIOx == GPIOB){         //reset macro do : rcc -> ahbrsts[0] &= ~(1 << 3)
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	}else if(pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE){
		GPIOE_REG_RESET();
	}else if(pGPIOx == GPIOF){
		GPIOF_REG_RESET();
	}else if(pGPIOx == GPIOG){
		GPIOG_REG_RESET();
	}else if(pGPIOx == GPIOH){
		GPIOH_REG_RESET();
	}else if(pGPIOx == GPIOI){
		GPIOI_REG_RESET();
	}
}


/***************************************************************************************************************************
 * @Function - GPIO_PeriClockControl
 * @Brief    - They control the peripheral clock of the GPIO pins
 * @Param1   - GPIO base address
 * @Param2   - ENABLE or DISABLE macros
 * @Param3   -
 * @Return   - None
 * @Note     - None
 **********************************************************************************************************************************/
void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		if(pGPIOx == GPIOA){                 //select gpio port and enable it. disable all other ports
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
	    }else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
	    }else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
	    }else if(pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
	    }else if(pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
	    }else if(pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
	    }else if(pGPIOx == GPIOI){
			GPIOI_PCLK_EN();
	    }
	}else
	{
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOF){
			GPIOF_PCLK_DI();
		}else if(pGPIOx == GPIOG){
			GPIOG_PCLK_DI();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_DI();
		}else if(pGPIOx == GPIOI){
			GPIOI_PCLK_DI();
		}
	}
}


/***************************************************************************************************************************
 * @Function - GPIO_ToggleOutputPin
 * @Brief    - It toggles the output pin of the GPIO peripheral
 * @Param1   - GPIO base address
 * @Param2   - Pin number of the GPIO peripheral(8 bit)
 * @Param3   -
 * @Return   - None
 * @Note     - None
 **********************************************************************************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx ->ODR ^= (1 << PinNumber);  // xor operation is used to toggle the pin
}

