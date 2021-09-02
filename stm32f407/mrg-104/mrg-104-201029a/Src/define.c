#include <stm32f4xx_hal.h>
#include "global_var.h"


#define  	STX                                    			0x02
#define  	ETX                                    			0x03
#define  	ACK                                    			0x06	

#define 	OVER_TIME                              	10//msec

#define  	COM_PORT1                       			1
#define  	COM_PORT2                             	2
#define  	COM_PORT3                             	3
#define  	COM_PORT4                             	4
#define  	COM_RS485                              	5


///rs-485 drive///
#define  	RS485_TX_ON                      			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
#define  	RS485_TX_OFF                          	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
#define  	RS485_RX_OFF                          	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
#define  	RS485_RX_ON                           	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
///////////////////

#define  	TEST_PIN_HIGH                         	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
#define  	TEST_PIN_LOW                          	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);



