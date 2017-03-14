# BBB-UART
BeagleBone Black UART library

- Add the files into your project.

- Include uart.h

- Dependency : the readBuffer output is stored in arrays as follows

        - You must have these variables in your project to use the respective UART.
        - extern char uartReadBuffer0[255], uartReadBuffer1[255], uartReadBuffer2[255], uartReadBuffer3[255], uartReadBuffer4[255];

# Initialization:

int uartInitialize(int uartNumber, int baudRate) : 

- uartNumber can be 0 to 4. This is BB-UARTx number

- baudRate can be 1200, 1800, 2400, 4800, 9600, 19200,and 38400

- Returns 

        0 - Initialization successful

        1 - Incorrect UART number
        
        2 - Incorrect baud rate
        
# Usage:

int uartWriteByte(int uartNumber, unsigned char uwb) :

- Sends a single byte over UART

- Returns 

        0 - Operation successful, 
        
        1 - Incorrect UART number

int uartWriteLine(int uartNumber, char uwl[]) :

- Sends a byte array over UART

- Returns 

        0 - Operation successful, 
        
        1 - Incorrect UART number

unsigned char uartRead(int uartNumber) :

- Reads the UART Buffer and saves it in the respective array

int uartDeinit(int uartNumber) :

- Deinitialize UART

- Returns 

        0 - Operation successful, 
        
        1 - Incorrect UART number
