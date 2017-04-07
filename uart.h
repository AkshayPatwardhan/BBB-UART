#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define UART_FUNCTION_SUCCESSFUL        0
#define UART_NUMBER_INCORRECT           1
#define UART_BAUDRATE_INCORRECT         2
#define UART_FIFO_ERROR                 3

unsigned char uartInitialize(int uartNumber, int baudRate);
unsigned char uartWriteByte(int uartNumber, unsigned char uwb);
unsigned char uartWriteLine(int uartNumber, unsigned char uwl[]);
unsigned char uartRead(int uartNumber);
unsigned char uartWaitTillTxComplete(int uartNumber);
unsigned char uartDeinit(int uartNumber);

#endif // UART_H
