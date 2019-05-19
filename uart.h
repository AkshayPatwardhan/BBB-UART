/*	
 *  Copyright (C) 2019  Akshay Patwardhan
 *  akshay.patwardhan@outlook.com
 *  
 *  Please go through readme.md for usage and other instructions, if any.
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Guarding macro start
#ifndef UART_H
#define UART_H

// Includes begin
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Error codes and return values
#define UART_FUNCTION_SUCCESSFUL        0
#define UART_NUMBER_INCORRECT           1
#define UART_BAUDRATE_INCORRECT         2
#define UART_FIFO_ERROR                 3
#define UART_INCORRECT_PATH             4

// Function declarations
unsigned char uartInitialize(int uartNumber, int baudRate);
unsigned char uartWriteByte(int uartNumber, unsigned char uwb);
unsigned char uartWriteLine(int uartNumber, unsigned char uwl[]);
unsigned char uartRead(int uartNumber);
unsigned char uartWaitTillTxComplete(int uartNumber);
unsigned char uartDeinit(int uartNumber);

// Guarding macro end
#endif // UART_H
