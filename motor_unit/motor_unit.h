/****************************************/
/*motor_unit.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_MOTOR_UNIT_H_
#define	_MOTOR_UNIT_H_



/****************************************/
#define	F_SAMPLE	500
#define	PPS_TO_MRPS	2182	/* PulsePerSample to MilradianPerSec */
						/* (6283 * F_SAMPLE) / ENCODER_PPR */

/****************************************/

/****************************************/
typedef struct MotorStat {
	signed long	current_milliamp;
	signed long	voltage_millivolt;
	signed long	millirad;			/* Position*/ 
	signed long	millirad_per_sec;	/* Speed */ 
	signed long	millirad_per_sec2;	/* Acceleration */
}MotorStat;
/****************************************/


/****************************************/
extern void	initializeMotorUnit( void );
extern signed long	driveMotorUnit( signed int motor_millivolt );
extern signed long	driveCurrentMotorUnit( signed short current_milliamp );
extern signed long	getVoltageMotorUnit( void );
extern signed long	getCurrentMotorUnit( void );
extern signed long	getPositionMotorUnit( void );
extern signed long	getSpeedMotorUnit( void );
/****************************************/

#endif	/*_MOTOR_UNIT_H_*/
