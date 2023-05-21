/* USER CODE BEGIN PM */
#define BUFFER_SIZE 20
/* USER CODE END PM */

/* USER CODE BEGIN PV */
uint32_t tick;
uint8_t transferring;
uint8_t Rx_buff[BUFFER_SIZE];
uint8_t Tx_buff[] = "From slave to master";
/* USER CODE END PV */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void I2C_Slave_Communicate(void)
{
  uint32_t index = 0;
  uint32_t timeout = 10000; // Set a timeout value for waiting for data reception

  I2C1->CR1 |= I2C_CR1_ACK;  //Acknowledge Enable

  // Wait for an I2C event
  while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_RXNE | I2C_SR1_TXE)));

  // Check if address matched and receive data or transmit data
  if (I2C1->SR1 & I2C_SR1_ADDR)
  {
    // Clear ADDR flag by reading SR1 and SR2
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    // Check if the master wants to write
    if (!(I2C1->SR2 & I2C_SR2_TRA))
    {
      // Master wants to write
      // Receive data bytes
      while (index != BUFFER_SIZE)
      {
        // Wait for data to be received
        timeout = 10000;
        while (!(I2C1->SR1 & I2C_SR1_RXNE) && --timeout);

        // Read the received data and store it in the buffer
        Rx_buff[index++] = I2C1->DR;
      }

      // Process received data or perform required actions
      printf((char*)Rx_buff);
      printf("\n");
      memset(Rx_buff, 0, strlen((char*)Rx_buff));
    }
    else
    {
      // Master wants to read
      // Transmit data bytes
      while(index != BUFFER_SIZE)
      {
        // Wait for the transmit buffer to be empty
        while(!(I2C1->SR1 & I2C_SR1_TXE));

        // Write the next byte to be transmitted and update the buffer index
        I2C1->DR = Tx_buff[index++];
      }
      // Process completion of transmission or perform required actions

    }
  }
  else if (I2C1->SR1 & I2C_SR1_RXNE)
  {
    // Discard received data if not addressed
    (void)I2C1->DR;
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		I2C_Slave_Communicate();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}
