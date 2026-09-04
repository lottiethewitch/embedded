#include "stm32f4xx_hal.h"

static void SystemClock_Config(void);

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  // GPIOA Clock - LED at PA5
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_5;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &gpio);

  while (1) {
	// TOGGLE PIN
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	HAL_Delay(500);

  } 

}

// Clock Configuration

static void SystemClock_Config(void) 
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

  HAL_RCC_OscConfig(&RCC_OscInitStruct);

}
