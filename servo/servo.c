/*
 * File:   servo.c
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <timer.h>

#include "servo.h"
#include "../motor_unit/motor_unit.h"
#include "logger/logger.h"

#define	_DEBUG
#include <assert/assert.h>
#include <xprintf/xprintf.h>
#include "../pin_assign.h"


/*******************************************/
static void initializeTimer(void);
static signed int pid(signed long reference_input, signed long mesured_output);
/*******************************************/


/*******************************************/
static signed long G_reference_millirad_per_sec;
static int G_is_servo_enabled = 0;
static long G_gain_kp = 20, G_gain_ki = 1, G_gain_kd = 0;//20:1:0
/*******************************************/


/*******************************************/

extern void initializeServo(void)
{
    initializeTimer();
    initLogger();
}


static void initializeTimer(void)
{
    unsigned int config;

    config = T1_ON & T1_IDLE_STOP & T1_GATE_OFF & T1_PS_1_64
            & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    OpenTimer1(config, 12500);
    ConfigIntTimer1(T1_INT_PRIOR_3 & T1_INT_ON);
}
/*******************************************/


/*******************************************/
extern signed long setReferenceServo(signed short rad_per_sec)
{
    G_reference_millirad_per_sec = (long)rad_per_sec * 100;

    return 0;
}
/*******************************************/




/*******************************************/
extern void enableServo(void)
{
    G_is_servo_enabled = 1;
}


extern void disableServo(void)
{
    G_is_servo_enabled = 0;
}
/*******************************************/



/*******************************************/
extern void setGainServo(long kp, long ki, long kd)
{
    G_gain_kp = kp;
    G_gain_ki = ki;
    G_gain_kd = kd;
}
/*******************************************/


static signed int pid(signed long reference_input, signed long mesured_output)
{
    static signed long err[3];
    static signed long long control_output[2];

    signed long long delta_control_output;
    signed long long control_output_minimize;

    /*指令値0時の初期化*/
    if(reference_input == 0){
        err[2] = 0;
        err[1] = 0;
        err[0] = 0;
        control_output[1] = 0;
        control_output[0] = 0;
    }
    /*偏差履歴を更新*/
    err[2] = err[1];
    err[1] = err[0];
    err[0] = reference_input - mesured_output;

    delta_control_output  = G_gain_kp * (err[0] - err[1]);
    delta_control_output += G_gain_ki *  err[0];
    delta_control_output += G_gain_kd * (err[0] - (2*err[1]) + err[2]);

    control_output[1] = control_output[0];
    control_output[0] = control_output[1] + delta_control_output;

    control_output_minimize = control_output[0] / 1024;

    if(control_output_minimize > SHRT_MAX){
        return SHRT_MAX;
    }
    if(control_output_minimize < SHRT_MIN){
        return SHRT_MIN;
    }
    return (signed short)control_output_minimize;
}
/*******************************************/


/*******************************************/
extern unsigned short getAllLogs(signed char* buf_ref, signed char* buf_mes)
{
    unsigned int i = 0;
    signed char temp_ref, temp_mes;

    while(getLogger(&temp_ref, &temp_mes) == SUCCESS_GETLOG){
        *(buf_ref + i) = temp_ref;
        *(buf_mes + i) = temp_mes;
        i++;
    }

    return i;
}
/*******************************************/

/*******************************************/
void _ISR _T1Interrupt(void)
{
    const unsigned int NUM_OF_LOOP_LOGGING_ = 4;	 /*2ms * 4 = 8msごとにログを取る*/
    static signed long output;
    static unsigned int	count_logging;
    signed int output_limited;
    signed long	measured_speed  = 0;
    signed int	shutdown_output = 0;
    unsigned char limit_check   = 0;
	
    _T1IF	= 0;

//	/*  電流リミッター */
//	const short	LIMIT_CURRENT_ = 2000;
//	static signed long	current_log[32];
//	static bool	is_current_overed = false;
//	static short	i;
//	signed long	average_current = 0,j;


    /*ログ動作*/
    measured_speed = getSpeedMotorUnit();
    limit_check = shutdownCurrentMotorUnit();
//	if( count_logging < NUM_OF_LOOP_LOGGING_ ){
//		count_logging ++;
//	}else{
//		count_logging	= 0;
//		setLogger( (signed char)(G_reference_millirad_per_sec / 1000 / 6), (signed char)(measured_speed / 1000 / 6) );
//	}

//    current_log[i]	= abs(getCurrentMotorUnit());
//	i++;
//	/* ロギング */
//	if( i>=32 ){
//		i	= 0;
//	}
//    average_current = 0;
//        for( j=0; j<32; j++ ){
//		average_current	+= current_log[j];
//    }
//    average_current = average_current >>  5;
//
//
//	/* 平均電流取得 */
//
//
//    if( average_current > LIMIT_CURRENT_ ){
//         is_current_overed	= true;
//
//    }else if( abs(G_reference_millirad_per_sec) < abs(getSpeedMotorUnit())){
//         is_current_overed	= false;
//	}
//
//
//
//	if( is_current_overed == true ){
//		if( G_reference_millirad_per_sec > 0 ){
//			driveCurrentMotorUnit( LIMIT_CURRENT_ );
//		}else{
//			driveCurrentMotorUnit( -LIMIT_CURRENT_ );
//		}
//	}else{
    if(limit_check == 1){
        shutdown_output = 0;
        driveMotorUnit( shutdown_output );

    }else{
        if(G_is_servo_enabled == 1){
            output = getVoltageMotorUnit();
            output += pid(G_reference_millirad_per_sec, measured_speed);

            if(output > 32767){
                output_limited = 32767;
                output = 32767;
            }else if(output < -32768){
                output_limited = -32768;
                output = -32768;
            }else{
                output_limited = output;
            }

            if(G_reference_millirad_per_sec == 0){
                output_limited = 0;
                output = 0;
            }

            driveMotorUnit(output_limited);
        }else{
            /*driveMotorUnit( G_reference_deg_per_sec );*/
        }
    }
}
/*******************************************/
