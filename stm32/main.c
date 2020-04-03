
#include "stm32f7xx_nucleo_144.h"
#include <stdio.h>
#define I2C_ADDRESS (0x22 << 1)
#define I2C_TIMING 0x10805E8B /* (Rise time = 120ns, Fall time = 25ns) */
#include<string.h> 
#define I2Cx I2C1
#define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define uint8_t unsigned char
#define I2Cx_FORCE_RESET() __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET() __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SDA_PIN GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SCL_SDA_AF GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn I2C1_EV_IRQn
#define I2Cx_ER_IRQn I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler I2C1_ER_IRQHandler

int transferState  = 0; //stop waiting getRegAdd, getData, sendData, getSize

char registerAddress = 0;
char size = 1;
char packet[255][512];
char transmitBuffer = 0;
char receiveBuffer = 0;
#define RXBUFFERSIZE 512

void shittyprint(char *toPrint){
	for(int i=0;i<strlen(toPrint);i++){
		ITM_SendChar(toPrint[i]);
	}
}
unsigned char* aRxBuffer[RXBUFFERSIZE];

 
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t direction, uint16_t addrMatchCode) { 
	switch (direction) {
		case I2C_DIRECTION_TRANSMIT:
			transferState = 2;
			if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &receiveBuffer, 1, I2C_FIRST_FRAME) != HAL_OK) {
				//Error();
			}
		break;
 
		case I2C_DIRECTION_RECEIVE:
			transferState = 4;
			
			transmitBuffer = aRxBuffer[registerAddress];
			//size = 512;
			if (HAL_I2C_Slave_Sequential_Transmit_IT(hi2c, &transmitBuffer, size, I2C_LAST_FRAME) != HAL_OK) {
				// Error here!!! (HAL_BUSY)
				
			}
		break;
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {

	switch (transferState) {
		case 2:
			registerAddress = receiveBuffer;
			if(registerAddress == 0x00){
				transferState = 3;
			}else{
				transferState = 5;
			}
			
			if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &size, 1, I2C_FIRST_FRAME) != HAL_OK) {
				//Error();
			}
		break;

		case 5: //Get Size

			transferState = 3;
			if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &packet, size, I2C_FIRST_FRAME) != HAL_OK) {
				//BSP_LED_On(LED_RED);
			}
			

			
		break;
		case 3:
			aRxBuffer[registerAddress] = packet;
			if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &receiveBuffer, 1, I2C_FIRST_FRAME) != HAL_OK) {
				//BSP_LED_On(LED_RED);
			}
					
		break;
	}
}
 
 
 
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c) { 
	HAL_I2C_EnableListen_IT(hi2c); // Restart
}
 
 
 
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
	if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		//Error();
	}
}
 
 

I2C_HandleTypeDef I2cHandle;
int main(void)
{
	HAL_Init();
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_RED);

	
	



	I2cHandle.Instance = I2Cx;
	I2cHandle.Init.Timing = I2C_TIMING;
	I2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
	I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.OwnAddress2 = 0xFF;
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	I2Cx_SCL_GPIO_CLK_ENABLE();
	I2Cx_SDA_GPIO_CLK_ENABLE();
	/* Enable I2Cx clock */
	I2Cx_CLK_ENABLE();


	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = I2Cx_SCL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
	/* I2C RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
	GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */

	/*##-3- Configure the NVIC for I2C ########################################*/
	/* NVIC for I2Cx */
	HAL_NVIC_SetPriority(I2Cx_ER_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(I2Cx_ER_IRQn);
	HAL_NVIC_SetPriority(I2Cx_EV_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(I2Cx_EV_IRQn);

	HAL_I2CEx_EnableFastModePlus(I2C_FASTMODEPLUS_I2C1);

	HAL_I2C_MspInit(&I2cHandle);
	shittyprint("HAL Init\n");
	if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
	{
		/* Initialization Error */
		BSP_LED_On(LED_RED);
		shittyprint("HAL Init Error");
		while (1)
		{
		}
	}



	shittyprint("HAL Enable Listen\n");
HAL_I2C_EnableListen_IT(&I2cHandle);

	transferState = 1;
  
  while(1)
  {


		
      //HAL_Delay(100);
    }

	return 0;
}


 
void I2C1_EV_IRQHandler(void)
{
	 ITM_SendChar((int)aRxBuffer[0] + '0');
	ITM_SendChar(' ');
	ITM_SendChar((int)aRxBuffer[1] + '0');
	ITM_SendChar(' ');
	ITM_SendChar((int)aRxBuffer[2] + '0');
	ITM_SendChar(' ');

    HAL_I2C_EV_IRQHandler(&I2cHandle); //I2CHandle is your I2C_HandleTypeDef object
}

void I2C1_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&I2cHandle);
}