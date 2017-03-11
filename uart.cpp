#include "uart.h"

#define BONEPATH	"/sys/devices/bone_capemgr.8/slots"

//UART config using termios
struct termios uartTermios,oldDescriptor;
int fileDescriptor0, fileDescriptor1, fileDescriptor2, fileDescriptor3, fileDescriptor4;
extern char uartReadBuffer0[255], uartReadBuffer1[255], uartReadBuffer2[255], uartReadBuffer3[255], uartReadBuffer4[255];

/*
 * Usage: uartInit(4,9600); - Initialize UART4 with Baudrate 9600
 *
 * Send Data: uartWriteByte('A'); - Send a single character on uartDeinit()
 *
 * Receive Data: uartRead(); - Read the UART buffer and store it in an array
*/

int uartInitialize(int uartNumber, int baudRate)
{
    FILE *uart;
    char buf[11] = "/dev/tty";
    int baud;

    //  Open the slot for UART
    uart = fopen(BONEPATH, "w");
    if(uart == NULL){
        printf("slots didn't open\n");
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
            return 1;
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
            return 1;
    }

    //save current attributes
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
            return 2;
    }

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
            return 1;
    }

    return 0;
}

int uartDeinit(int uartNumber){
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
    return 0;
}

int uartWriteByte(int uartNumber, unsigned char uwb){
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
        return 1;
    }
    return 0;
}

int uartWriteLine(int uartNumber, char uwl[])
{
    int ii;
    ii = strlen(uwl);
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
        return 1;
    }
    return 0;
}

unsigned char uartRead(int uartNumber){

    switch(uartNumber){
    case 0:
        return read(fileDescriptor0,&uartReadBuffer0[0],255);
        break;
    case 1:
        return read(fileDescriptor1,&uartReadBuffer1[0],255);
        break;
    case 2:
        return read(fileDescriptor2,&uartReadBuffer2[0],255);
        break;
    case 3:
        return read(fileDescriptor3,&uartReadBuffer3[0],255);
        break;
    case 4:
        return read(fileDescriptor4,&uartReadBuffer4[0],255);
        break;
    default:
        printf("Incorrect UART number");
        return 1;
    }

    return 0;
}
