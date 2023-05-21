# STM32-I2C-slave
This is a functional c code to use I2C peripheral without using HAL and without the slave knowing the order of transmit or receive. 

instead of using HAL_I2C_Slave_Transmit and HAL_I2C_Slave_Receive and their varients (IT or DMA), which the order of transmission between master and slave should be agreed upon beforehand, we could use the baremetal approach.
just initialize the I2C peripheral using STM32CubeMX (or STM32CubeIDE) and copy the given codes in main.c file to the corresponding location in your project.
