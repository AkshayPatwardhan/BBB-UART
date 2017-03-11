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


int uartInitialize(int uartNumber, int baudRate);
int uartWriteByte(int uartNumber, unsigned char uwb);
int uartWriteLine(int uartNumber, char uwl[]);
unsigned char uartRead(int uartNumber);
int uartDeinit(int uartNumber);

#endif // UART_H
