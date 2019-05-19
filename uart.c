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

#include uart.h

// ----------------Beaglebone Black UART defines and global variables start----------------

// Added another condition in uartInitialize function to take care of both conditions and 
// choose whichever cape is present. (Priority given to bone_capemgr.9)
// Define the beaglebone black cape. The cape manager may be 8 or 9
#define BONEPATH_9	"/sys/devices/bone_capemgr.9/slots"
#define BONEPATH_8	"/sys/devices/bone_capemgr.8/slots"

//UART config using termios
struct termios uartTermios,oldDescriptor;

// File descriptors for UART0-4
int fileDescriptor0, fileDescriptor1, fileDescriptor2, fileDescriptor3, fileDescriptor4;

// This is my implementation of read buffers. In my application, i have set these buffers as global arrays in
//      my main.c -- so I am referring them here as extern
// You may use static or define them here or whatever. The important thing is the uartRead will use this precise file
//      name to store the read data. So change this carefully.
extern char uartReadBuffer0[64], uartReadBuffer1[64], uartReadBuffer2[64], uartReadBuffer3[64], uartReadBuffer4[64];

// ----------------Beaglebone Black UART defines and global variables end----------------

/*
 * Beaglebone Black UART Functions
 *
 * Usage:
 *
 * unsigned char uartInitialize(int uartNumber, int baudRate)
 *  - Initializes a specific UART peripheral with given baudrate
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *                      int baudRate - UART baudrate
 *                                     - Valid values - 1200, 1800, 2400, 4800, 9600, 19200, 38400
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *                      UART_BAUDRATE_INCORRECT - UART baudrate entered is incorrect
 *                      UART_INCORRECT_PATH - unable to open slots for both bone_capemgr.9 & bone_capemgr.8
 *
 *  unsigned char uartDeinit(int uartNumber)
 *  - Deinitializes UART peripheral
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *
 *  unsigned char uartWriteByte(int uartNumber, unsigned char uwb)
 *  - Write a single byte to UART
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *                      unsigned char uwb - Byte to be written to UART
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *
 *  unsigned char uartWriteLine(int uartNumber, unsigned char uwl[])
 *  - Write a byte array to UART
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *                      unsigned char[] uwl - Byte array to be written to UART
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *                      UART_FIFO_ERROR - Character array passed has exceeds Transmit FIFO size
 *
 *  unsigned char uartRead(int uartNumber)
 *  - UART Receive FIFO is copied into the global array uartReadBufferX
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *
 *  unsigned char uartWaitTillTxComplete(int uartNumber)
 *  - Wait till UART transmission is complete.
 *  - Input param   :   int uartNumber - UART number to initialize.
 *                                     - Valid values - 0 to 4
 *  - Return param  :   UART_FUNCTION_SUCCESSFUL - Function completed successfully
 *                      UART_NUMBER_INCORRECT - UART number entered is incorrect
 *
 */

//  Beaglebone Black UART functions start

unsigned char uartInitialize(int uartNumber, int baudRate)
{
    FILE *uart;
    char buf[11] = "/dev/tty";
    int baud;

    // Open the slot for UART
    // Try for bone_capemgr.9 first
    uart = fopen(BONEPATH_9, "w");
    if(uart == NULL){
        printf("bone_capemgr.9 doesn't exist. Trying bone_capemgr.8");
        uart = fopen(BONEPATH_8, "w");
        if(uart == NULL){
            printf("slots didn't open\n");
            return UART_INCORRECT_PATH;
        }
    }
    fseek(uart,0,SEEK_SET);

    switch(uartNumber){
        case 0:
            fprintf(uart, "BB-UART1");
            strcat(buf, "O0");
            break;
        case 1:
            fprintf(uart, "BB-UART2");
            strcat(buf, "O1");
            break;
        case 2:
            fprintf(uart, "BB-UART3");
            strcat(buf, "O2");
            break;
        case 3:
            fprintf(uart, "BB-UART4");
            strcat(buf, "O3");
            break;
        case 4:
            fprintf(uart, "BB-UART5");
            strcat(buf, "O4");
            break;
        default:
            printf("Uart modules are 0-4\n");
            return UART_NUMBER_INCORRECT;
    }
    fflush(uart);
    fclose(uart);

    //  Open uart port for UART tx/rx
    switch(uartNumber){
        case 0:
            fileDescriptor0 = open(buf, O_RDWR | O_NOCTTY);
            if(fileDescriptor0 < 0){
                printf("port failed to open\n");
            }
            break;
        case 1:
            fileDescriptor1 = open(buf, O_RDWR | O_NOCTTY);
            if(fileDescriptor1 < 0){
                printf("port failed to open\n");
            }
            break;
        case 2:
            fileDescriptor2 = open(buf, O_RDWR | O_NOCTTY);
            if(fileDescriptor2 < 0){
                printf("port failed to open\n");
            }
            break;
        case 3:
            fileDescriptor3 = open(buf, O_RDWR | O_NOCTTY);
            if(fileDescriptor3 < 0){
                printf("port failed to open\n");
            }
            break;
        case 4:
            fileDescriptor4 = open(buf, O_RDWR | O_NOCTTY);
            if(fileDescriptor4 < 0){
                printf("port failed to open\n");
            }
            break;
        default:
            printf("Incorrect UART number");
            return UART_NUMBER_INCORRECT;
    }

    //save current attributes
    // Edit: Removed the line saving old attributes. Not needed usually.
//    tcgetattr(fileDescriptor,&oldDescriptor);
    bzero(&uartTermios,sizeof(uartTermios));
    switch(baudRate){
        case 1200:
            baud = B1200;
            break;
        case 1800:
            baud = B1800;
            break;
        case 2400:
            baud = B2400;
            break;
        case 4800:
            baud = B4800;
            break;
        case 9600:
            baud = B9600;
            break;
        case 19200:
            baud = B19200;
            break;
        case 38400:
            baud = B38400;
            break;
        default:
            printf("Incorrect baud rate");
            return UART_BAUDRATE_INCORRECT;
    }

    // Choose the control/input/output/local modes for UART operation
    // I would suggest you read the manual here: http://man7.org/linux/man-pages/man3/termios.3.html
    uartTermios.c_cflag = baud | CS8 | CLOCAL | CREAD;
    uartTermios.c_iflag = IGNPAR | ICRNL | IGNCR;
    uartTermios.c_oflag = 0;
    uartTermios.c_lflag = 0;

    uartTermios.c_cc[VTIME] = 0;
    uartTermios.c_cc[VMIN]  = 0;

    // Clean the line and set the attributes
    switch(uartNumber){
        case 0:
            tcflush(fileDescriptor0,TCIFLUSH);
            tcsetattr(fileDescriptor0,TCSANOW,&uartTermios);
            break;
        case 1:
            tcflush(fileDescriptor1,TCIFLUSH);
            tcsetattr(fileDescriptor1,TCSANOW,&uartTermios);
            break;
        case 2:
            tcflush(fileDescriptor2,TCIFLUSH);
            tcsetattr(fileDescriptor2,TCSANOW,&uartTermios);
            break;
        case 3:
            tcflush(fileDescriptor3,TCIFLUSH);
            tcsetattr(fileDescriptor3,TCSANOW,&uartTermios);
            break;
        case 4:
            tcflush(fileDescriptor4,TCIFLUSH);
            tcsetattr(fileDescriptor4,TCSANOW,&uartTermios);
            break;
        default:
            printf("Incorrect UART number");
            return UART_NUMBER_INCORRECT;
    }

    return UART_FUNCTION_SUCCESSFUL;
}

unsigned char uartDeinit(int uartNumber)
{
    switch(uartNumber){
        case 0:
            close(fileDescriptor0);
            break;
        case 1:
            close(fileDescriptor1);
            break;
        case 2:
            close(fileDescriptor2);
            break;
        case 3:
            close(fileDescriptor3);
            break;
        case 4:
            close(fileDescriptor4);
            break;
        default:
            printf("Incorrect UART number");
            break;
    }
    return UART_FUNCTION_SUCCESSFUL;
}

unsigned char uartWriteByte(int uartNumber, unsigned char uwb)
{
    switch(uartNumber){
    case 0:
        write(fileDescriptor0,&uwb,1);
        break;
    case 1:
        write(fileDescriptor1,&uwb,1);
        break;
    case 2:
        write(fileDescriptor2,&uwb,1);
        break;
    case 3:
        write(fileDescriptor3,&uwb,1);
        break;
    case 4:
        write(fileDescriptor4,&uwb,1);
        break;
    default:
        printf("Incorrect UART number");
        return UART_NUMBER_INCORRECT;
    }
    return UART_FUNCTION_SUCCESSFUL;
}

unsigned char uartWriteLine(int uartNumber, unsigned char uwl[])
{
    unsigned int ii;
    ii = strlen(uwl);
    if(strlen > 64){
        return UART_FIFO_ERROR;
    }
    else{
        switch(uartNumber){
        case 0:
            write(fileDescriptor0,uwl,ii);
            break;
        case 1:
            write(fileDescriptor1,uwl,ii);
            break;
        case 2:
            write(fileDescriptor2,uwl,ii);
            break;
        case 3:
            write(fileDescriptor3,uwl,ii);
            break;
        case 4:
            write(fileDescriptor4,uwl,ii);
            break;
        default:
            printf("Incorrect UART number");
            return UART_NUMBER_INCORRECT;
        }
    }
    return UART_FUNCTION_SUCCESSFUL;
}

unsigned char uartRead(int uartNumber)
{
    switch(uartNumber){
    case 0:
        return read(fileDescriptor0,&uartReadBuffer0[0],64);
        break;
    case 1:
        return read(fileDescriptor1,&uartReadBuffer1[0],64);
        break;
    case 2:
        return read(fileDescriptor2,&uartReadBuffer2[0],64);
        break;
    case 3:
        return read(fileDescriptor3,&uartReadBuffer3[0],64);
        break;
    case 4:
        return read(fileDescriptor4,&uartReadBuffer4[0],64);
        break;
    default:
        printf("Incorrect UART number");
        return UART_NUMBER_INCORRECT;
    }

    return UART_FUNCTION_SUCCESSFUL;
}

unsigned char uartWaitTillTxComplete(int uartNumber){
    switch(uartNumber){
    case 0:
        tcdrain(fileDescriptor0);
        break;
    case 1:
        tcdrain(fileDescriptor1);
        break;
    case 2:
        tcdrain(fileDescriptor2);
        break;
    case 3:
        tcdrain(fileDescriptor3);
        break;
    case 4:
        tcdrain(fileDescriptor4);
        break;
    default:
        printf("Incorrect UART number");
        return UART_NUMBER_INCORRECT;
    }
    return UART_FUNCTION_SUCCESSFUL;
}

//  Beaglebone Black UART functions end
