
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "KEY&LED.h"
#include "usart.h"
#define BUZZER_PIN GPIO_Pin_2 
#define BUZZER_PORT GPIOB 

void Buzzer_Config(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
		
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = BUZZER_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // Initialize the buzzer pin
    GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

    // Turn off the buzzer initially
    GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
}
void percentConvertor(uint16_t currentValue)
{
	uint16_t x;
	x=currentValue/480;
	printf("Analog sensor value in %u \r\n", currentValue);
	
}

void ADC_Config(void) {
    ADC_InitTypeDef ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // Enable the clock for GPIOA and ADC1
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // Configure the pin as analog input
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // Assuming the analog sensor is connected to PA0
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure ADC parameters
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion = 1;
		
    ADC_Init(ADC1, &ADC_InitStruct);

    // Enable ADC
    ADC_Cmd(ADC1, ENABLE);

    // Enable ADC channel
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);  // Use the desired sample time
}
// Function to read data from the analog sensor
uint16_t Read_AnalogSensor(void) {
    // Start ADC conversion
    ADC_SoftwareStartConv(ADC1);

    // Wait for conversion to complete
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    // Read ADC value
    return ADC_GetConversionValue(ADC1);
}

// Simple delay function
void delay(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 2000; j++); // Adjust this loop for your clock speed
}





 

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
 
  RCC_ClocksTypeDef SYS_Clocks;
	
  /* USART configuration */
  USART_Config();  
	ADC_Config();
	Buzzer_Config();

	
 
  RCC_GetClocksFreq(&SYS_Clocks);
	printf("\r\nSYSCLK:%dM\r\n",SYS_Clocks.SYSCLK_Frequency/1000000);
	printf("HCLK:%dM\r\n",SYS_Clocks.HCLK_Frequency/1000000);
	printf("PCLK1:%dM\r\n",SYS_Clocks.PCLK1_Frequency/1000000);
	printf("PCLK2:%dM\r\n",SYS_Clocks.PCLK2_Frequency/1000000);	
	printf("\n\r KEY Example \r\n");
		JOYState_LED_GPIO_Init();
  while (1)
  {
		uint16_t sensVal = Read_AnalogSensor();
		
		
		
		if (sensVal > 40000) {
            // Turn on the buzzer
            GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
            delay(1000);
            // Turn off the buzzer
            GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
        }
		percentConvertor(sensVal);
    delay(1000);   
	
	}
	
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
