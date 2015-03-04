/*
 * File:   main.c
 * Ver 1.0.1
 *
 * Author: Ishikura Makito
 *
 * Created on 2012/07/20, 18:13
 */

#define	FCY 39613750

#include <xc.h>
#include <libpic30.h>

#include "main.h"
#include "pin_assign.h"
#include "motor_unit/motor_unit.h"
#include "comm/comm.h"
#include "servo/servo.h"
#include "servo/logger/logger.h"

#include <assert/assert.h>
#include <uart_dsPIC33F/uart_dsPIC33F.h>

#include <xprintf/xprintf.h>
/********************************************************/


/********************************************************/
static void sendLogToMain(void);
static void executeOrder(Order order);
/********************************************************/

int main(void)
{
    initialize();
    initializeComm();
    initializeMotorUnit();
    initializeServo();

    xdev_out(putcUart);

    Order order;
//    signed long i;

    while(1){
        order = fetchOrder();
        executeOrder(order);
        sendLogToMain();
    }
}

/********************************************************/

static void sendLogToMain(void)
{
    unsigned short num_of_logs;
    static signed char ref[16], mes[16];
    short err;

    num_of_logs	= getAllLogs(ref, mes);
    err = sendLogs(num_of_logs, ref, mes);
}


/********************************************************/
static void executeOrder(Order order)
{
    switch(order.command){
    case COMMAND_SPEED_PID:
        enableServo();
        setReferenceServo(order.data[0]);
        break;

    case COMMAND_SPEED_OPENLOOP:
        disableServo();
        driveMotorUnit(order.data[0]);
        break;


    case COMMAND_PID_GAIN:
        setGainServo(order.data[0], order.data[1], order.data[2]);
        break;

    default:
        break;
    }

}

/********************************************************/
void initialize(void)
{
    initializeOsc();
    initializeIO();
}


void initializeOsc(void)
{
    RCONbits.SWDTEN = 0;

    _PLLPOST = 0b00;    /* N2:  PLL出力分周 = 2 */
    _PLLPRE = 0b0000;   /* N1:  PLL入力プリスケーラ = 2*/
    PLLFBD  = 0x0029;   /* M :  PLL倍率 = 43 */

    while(!OSCCONbits.LOCK); /* waiting PLL Lock */
}


void initializeIO(void)
{
    PORTA = 0x0000;
    TRISA = 0x0000;

    PORTB = 0x0000;
    TRISB = 0x0000;
}


/********************************************************/



/********************************************************/
/*テストコード*/
#ifdef _DEBUG
#endif


/********************************************************/



