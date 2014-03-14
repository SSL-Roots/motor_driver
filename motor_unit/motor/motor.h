/****************************************/
/*motor.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_MOTOR_H_
#define	_MOTOR_H_



/****************************************/
#define	CW		0
#define	CCW		1
#define	BRAKE	2

#define	KN	374
#define	KT	26
#define	MOTOR_R_MILLIOHM	1200
/****************************************/



/****************************************/
void	initializeMotor( void );
unsigned char	driveMotor( signed int motor_millivolt );
/****************************************/

/**************************************/
/*テストコード*/
/**************************************/
void	Test_driveMotor_sinWave( signed int max_voltage, unsigned char num_loop, unsigned long period_ms );
void	Test_driveMotor_bangbang( signed int voltage, unsigned char num_loop, unsigned long period_ms );
#ifdef	_DEBUG
void	Test_driveMotor( void );
void	Test_getFowardExcitationPhase( void );
void	Test_getBackwardExcitationPhase( void );
void	Test_getDicretion( void );
void	Test_getDuty( void );
#endif

#endif	/*_MOTOR_H_*/
