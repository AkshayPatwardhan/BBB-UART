# About

I initially created and uploaded this library on github for my own backup and as a reference to my co-workers. Lately, to my surprise, this library has been getting a lot of traction. So I've decided to add GNU GPLv3 so anyone can officially use this in their own projects, public or commercial.

This is a motivator for me, and I might just go ahead and start creating a one-stop-shop libraries for other BBB peripherals as well. Let me know if any of you specifically want me to develop something in my free time.

You can contact me at akshay.patwardhan@outlook.com

# BBB-UART
This is a simple BeagleBone Black UART library

- Add the files into your project.

- Include uart.h

# Usage

## unsigned char uartInitialize(int uartNumber, int baudRate)
- Initializes a specific UART peripheral with given baudrate
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
#### int baudRate 
- UART baudrate
- Valid values - 1200, 1800, 2400, 4800, 9600, 19200, 38400
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
- UART_BAUDRATE_INCORRECT - UART baudrate entered is incorrect
- UART_INCORRECT_PATH - Slots didn't open for both bone_capemgr.9 and bone_capemgr.8
## unsigned char uartDeinit(int uartNumber)
- Deinitializes UART peripheral
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
## unsigned char uartWriteByte(int uartNumber, unsigned char uwb)
- Write a single byte to UART
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
## unsigned char uartWriteLine(int uartNumber, unsigned char uwl[])
- Write a byte array to UART
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
#### unsigned char[] uwl 
- Byte array to be written to UART
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
- UART_FIFO_ERROR - Character array passed has exceeds Transmit FIFO size
## unsigned char uartRead(int uartNumber)
- UART Receive FIFO is copied into the global array uartReadBufferX
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
## unsigned char uartWaitTillTxComplete(int uartNumber)
- Wait till UART transmission is complete.
### Input param   :   
#### int uartNumber 
- UART number to initialize.
- Valid values - 0 to 4
### Return param  :   
- UART_FUNCTION_SUCCESSFUL - Function completed successfully
- UART_NUMBER_INCORRECT - UART number entered is incorrect
