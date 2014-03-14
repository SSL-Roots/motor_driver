/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#ifndef	_BRIDGE_H_
#define	_BRIDGE_H_


/**************************************/
/*#define	DO_TEST*/
/**************************************/

/**************************************/
#define	FET_1H	PWM1_POUT_3L
#define	FET_1L	PWM1_POUT_3H
#define	FET_2H	PWM1_POUT_2L
#define	FET_2L	PWM1_POUT_2H
#define	FET_3H	PWM1_POUT_1L
#define	FET_3L	PWM1_POUT_1H
#define	FET_1H_OFF	PWM1_POUT3L_INACT
#define	FET_1H_ON	PWM1_POUT3L_ACT
#define	FET_1L_OFF	PWM1_POUT3H_INACT
#define	FET_1L_ON	PWM1_POUT3H_ACT
#define	FET_2H_OFF	PWM1_POUT2L_INACT
#define	FET_2H_ON	PWM1_POUT2L_ACT
#define	FET_2L_OFF	PWM1_POUT2H_INACT
#define	FET_2L_ON	PWM1_POUT2H_ACT
#define	FET_3H_OFF	PWM1_POUT1L_INACT
#define	FET_3H_ON	PWM1_POUT1L_ACT
#define	FET_3L_OFF	PWM1_POUT1H_INACT
#define	FET_3L_ON	PWM1_POUT1H_ACT
/**************************************/

/**************************************/
#define	EXCITATION_BRAKE	0
#define	EXCITATION_3_2		32
#define	EXCITATION_1_2		12
#define	EXCITATION_1_3		13
#define	EXCITATION_2_3		23
#define	EXCITATION_2_1		21
#define	EXCITATION_3_1		31
/**************************************/



/**************************************/
#define	BRIDGE_1	1
#define	BRIDGE_2	2
#define	BRIDGE_3	3
/**************************************/


/**************************************/
void	initializeBridge( void );
extern void	driveBridge( unsigned char phase );
extern void	setDutyBridge( unsigned int duty_int );
/**************************************/


/**************************************/
#ifdef	DO_TEST

void	Test_pinAssign( void );
void	Test_calculatePR( void );
void	Test_driveBridge( void );

#endif
/**************************************/

#endif	/*_BRIDGE_H_*/
