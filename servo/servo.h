/*
 * File:   servo.h
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */

#ifndef	_SERVO_H_
#define	_SERVO_H_

/*******************************************/
extern void initializeServo(void);
extern signed long  setReferenceServo(signed short rad_per_sec);
extern void setGainServo(long kp, long ki, long kd);
extern void enableServo(void);
extern void disableServo(void);
/*******************************************/
extern unsigned short getAllLogs(signed char* buf_ref, signed char* buf_mes);
/*******************************************/

#endif	/*_SERVO_H_*/
