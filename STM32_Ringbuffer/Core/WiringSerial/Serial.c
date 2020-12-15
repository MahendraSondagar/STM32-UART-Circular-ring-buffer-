/*
 * Serial.c
 *
 *  Created on: 10-Dec-2020
 *      Author: mahendra
 */

#include "Serial.h"

int rx_buffer_head1 = 0;
int rx_buffer_tail1 = 0;
int rx_buffer_head2 = 0;
int rx_buffer_tail2 = 0;

unsigned char rx_buffer1[RX_BUFFER_SIZE_1];
unsigned char rx_buffer2[RX_BUFFER_SIZE_2];
UART_HandleTypeDef huart2;


Wiring_Serial_t Serial =
{
	  Serialbegin,
  	  Serialclose,
	  SerialWrite,
	  SerialAvailable,
	  SerialRead,
	  SerialFlush,
	  SerialprintMode,
	  SerialprintString,
	  SerialprintIntegerInBase,
	  Serialputhex,
	  SerialprintInteger,
	  SerialprintHexlong,
	  SerialprintOctal,
	  SerialprintBinary
};


// connects the internal peripheral in the processor and configures it
void Serialbegin(long baud, uint8_t portNum)
{

	// defaults to 8-bit, no parity, 1 stop bit

	switch(portNum)
	{
	case 1:
		 /* USER CODE BEGIN USART1_Init 0 */

		  /* USER CODE END USART1_Init 0 */

		  /* USER CODE BEGIN USART1_Init 1 */

		  /* USER CODE END USART1_Init 1 */
		  huart1.Instance = USART1;
		  huart1.Init.BaudRate = 115200;
		  huart1.Init.WordLength = UART_WORDLENGTH_8B;
		  huart1.Init.StopBits = UART_STOPBITS_1;
		  huart1.Init.Parity = UART_PARITY_NONE;
		  huart1.Init.Mode = UART_MODE_TX_RX;
		  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
		  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
		  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		  if (HAL_UART_Init(&huart1) != HAL_OK)
		  {
		    Error_Handler();
		  }
		  delay(500);
		  HAL_UART_Receive_IT(&huart1, (uint8_t *)rx1_temp, 1);
		  /* USER CODE END USART1_Init 2 */

		break;
	case 2:

		    /* USER CODE BEGIN USART2_Init 0 */

			/* USER CODE END USART2_Init 0 */

			/* USER CODE BEGIN USART2_Init 1 */

			/* USER CODE END USART2_Init 1 */
		  huart2.Instance = USART2;
		  huart2.Init.BaudRate = 115200;
		  huart2.Init.WordLength = UART_WORDLENGTH_8B;
		  huart2.Init.StopBits = UART_STOPBITS_1;
		  huart2.Init.Parity = UART_PARITY_NONE;
		  huart2.Init.Mode = UART_MODE_TX_RX;
		  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
		  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
		  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		  if (HAL_UART_Init(&huart2) != HAL_OK)
		  {
		    Error_Handler();
		  }
		  delay(500);
		  HAL_UART_Receive_IT(&huart2, (uint8_t *)rx2_temp, 1);
			/* USER CODE END USART2_Init 2 */

		break;

	default :

		break;
	}

}


// disconnects the internal peripheral in the processor
void Serialclose(uint8_t portNum)
{
  switch(portNum)
  {
  case 1:
	  HAL_UART_DeInit(&huart1);
	  break;
  case 2:
	  HAL_UART_DeInit(&huart2);
	  break;
  default:
	  break;
  }
}


void SerialWrite(unsigned char c, uint8_t portNum)
{
	 switch(portNum)
	 {
	 case 1:
		 HAL_UART_Transmit(&huart1, &c, 1, SERIAL_DEFAULT_TIMEOUT);
		 break;
	 case 2:
		 HAL_UART_Transmit(&huart2, &c, 1, SERIAL_DEFAULT_TIMEOUT);
		 break;
	 default :
		 break;
	 }
}

int SerialAvailable(uint8_t portNum)
{
	switch(portNum)
	{
	case 1:
		return (RX_BUFFER_SIZE_1 + rx_buffer_head1 - rx_buffer_tail1) % RX_BUFFER_SIZE_1;
		break;
	case 2:
		return (RX_BUFFER_SIZE_2 + rx_buffer_head2 - rx_buffer_tail2) % RX_BUFFER_SIZE_2;
		break;
	default:
		break;
	}
}

int SerialRead(uint8_t portNum)
{
	switch(portNum)
	{
	case 1:
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head1 == rx_buffer_tail1) {
					return -1;
				} else {
					unsigned char c = rx_buffer1[rx_buffer_tail1];
					rx_buffer_tail1 = (rx_buffer_tail1 + 1) % RX_BUFFER_SIZE_1;
					return c;
				}
		break;
	case 2:
		// if the head isn't ahead of the tail, we don't have any characters
				if (rx_buffer_head2 == rx_buffer_tail2) {
					return -1;
				} else {
					unsigned char c = rx_buffer2[rx_buffer_tail2];
					rx_buffer_tail2 = (rx_buffer_tail2 + 1) % RX_BUFFER_SIZE_2;
					return c;
				}
		break;
	default:
		break;
	}
}

void SerialFlush(uint8_t portNum)
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.

	switch(portNum)
	{
	case 1:
		rx_buffer_tail1=0;
	    rx_buffer_head1 = rx_buffer_tail1;
		break;
	case 2:
		rx_buffer_tail2=0;
	    rx_buffer_head2 = rx_buffer_tail2;
		break;
	default :
		break;
	}
}


void SerialprintMode(int mode, uint8_t portNum)
{
	// do nothing, we only support serial printing, not lcd.
}

void SerialprintByte(unsigned char c, uint8_t portNum)
{
	SerialWrite(c, portNum);
}

void SerialSerialprintNewline(uint8_t portNum)
{
	SerialprintByte('\r', portNum);
	SerialprintByte('\n', portNum);
}

void SerialprintString(const char *s, uint8_t portNum)
{
	switch(portNum)
	{
	case 1:
		HAL_UART_Transmit(&huart1, (uint8_t *)s, strlen(s), SERIAL_DEFAULT_TIMEOUT);
		break;

	case 2:
		HAL_UART_Transmit(&huart2, (uint8_t *)s, strlen(s), SERIAL_DEFAULT_TIMEOUT);
		break;

	default :
		break;
	}

}

void SerialprintIntegerInBase(unsigned long n, unsigned long base, uint8_t portNum)
{
	unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
	unsigned long i = 0;

	if (n == 0) {
		SerialprintByte('0', portNum);
		return;
	}

	while (n > 0) {
		buf[i++] = n % base;
		n /= base;
	}

	for (; i > 0; i--)
		SerialprintByte(buf[i - 1] < 10 ?
			'0' + buf[i - 1] :
			'A' + buf[i - 1] - 10, portNum);
}


void Serialputhex(char ch, uint8_t portNum) {
    char ah,al;

    ah = (ch & 0xf0) >> 4;
    if(ah >= 0x0a) {
	ah = ah - 0x0a + 'A';
    } else {
	ah += '0';
    }
    al = (ch & 0x0f);
    if(al >= 0x0a) {
	al = al - 0x0a + 'A';
    } else {
	al += '0';
    }
    SerialprintByte(ah, portNum);
    SerialprintByte(al, portNum);
}



void SerialprintInteger(long n, uint8_t portNum)
{
	if (n < 0) {
		SerialprintByte('-', portNum);
		n = -n;
	}

	SerialprintIntegerInBase(n, 10, portNum);
}

void SerialprintHexlong(unsigned long n, uint8_t portNum)
{
	SerialprintIntegerInBase(n, 16, portNum);
}

void SerialprintOctal(unsigned long n, uint8_t portNum)
{
	SerialprintIntegerInBase(n, 8, portNum);
}

void SerialprintBinary(unsigned long n, uint8_t portNum)
{
	SerialprintIntegerInBase(n, 2, portNum);
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
	 if(huart->Instance== USART2)
	 {
		 unsigned char buff = rx2_temp[0];
		 int i = (rx_buffer_head2 + 1) % RX_BUFFER_SIZE_2;
		 // if we should be storing the received character into the location
		 // just before the tail (meaning that the head would advance to the
		 // current location of the tail), we're about to overflow the buffer
		 // and so we don't write the character or advance the head.
		 if (i != rx_buffer_tail2) {
		 	 rx_buffer2[rx_buffer_head2] = buff;
		 	 rx_buffer_head2 = i;
		 	 }
		 HAL_UART_Receive_IT(&huart2, (uint8_t *)rx2_temp, 1);
	 }

	 if(huart->Instance== USART1)
	 	 {
	 		 unsigned char buff = rx1_temp[0];
	 		 int i = (rx_buffer_head1 + 1) % RX_BUFFER_SIZE_1;
	 		 // if we should be storing the received character into the location
	 		 // just before the tail (meaning that the head would advance to the
	 		 // current location of the tail), we're about to overflow the buffer
	 		 // and so we don't write the character or advance the head.
	 		 if (i != rx_buffer_tail1) {
	 		 	 rx_buffer1[rx_buffer_head1] = buff;
	 		 	 rx_buffer_head1 = i;
	 		 	 }
	 		 HAL_UART_Receive_IT(&huart1, (uint8_t *)rx1_temp, 1);
	 	 }

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
}


/* Including print() adds approximately 1500 bytes to the binary size,
 * so we replace it with the smaller and less-confusing printString(),
 * printInteger(), etc.
void print(const char *format, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 256, format, ap);
	va_end(ap);

	printString(buf);
}
*/
