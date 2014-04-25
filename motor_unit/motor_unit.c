/****************************************/
/*motor_unit.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
#include	<timer.h>
#include	<limits.h>
#include	<xprintf/xprintf.h>
#include	"motor_unit.h"
#include	"motor/motor.h"
#include	"encorder/encorder.h"

/****************************************/
/*#define	_DEBUG*/
#include	<assert/assert.h>
/****************************************/

#define	RND_TO_MILLIRAD	6283
#define	RAD_PER_SEC_TO_RND_PER_MIN	10	

/****************************************/
static void	initializeTimer( void );
static signed short	calculateCurrent( signed short voltage_millivolt, signed long deg_per_sec );
MotorStat	G_motor_stat;
/****************************************/


/****************************************/
extern void	initializeMotorUnit( void )
{
	initializeMotor();
    initializeEncorder();
    initializeTimer();
}
/****************************************/


/****************************************/
extern signed long	driveMotorUnit( signed int motor_millivolt )
{
	G_motor_stat.voltage_millivolt	= motor_millivolt;
	driveMotor( motor_millivolt );
	return	G_motor_stat.millirad_per_sec;
}


extern signed long	driveCurrentMotorUnit( signed short current_milliamp )
{
	signed long	voltage_millivolt = MOTOR_R_MILLIOHM * (long)current_milliamp / 1000 + G_motor_stat.millirad_per_sec*RAD_PER_SEC_TO_RND_PER_MIN/KN;

	if( voltage_millivolt > SHRT_MAX ){
		voltage_millivolt	= SHRT_MAX;
	}else if( voltage_millivolt < SHRT_MIN ){
		voltage_millivolt	= SHRT_MIN;
	}

	G_motor_stat.voltage_millivolt	= (short)voltage_millivolt;
	driveMotor( voltage_millivolt );

	return	0;
}
/****************************************/


/****************************************/
extern signed short	getVoltageMotorUnit( void )
{
	return	G_motor_stat.voltage_millivolt;
}


extern signed short	getCurrentMotorUnit( void )
{
	return	G_motor_stat.current_milliamp;
}

extern signed long	getPositionMotorUnit( void )
{
	return	G_motor_stat.millirad;
}

extern signed long	getSpeedMotorUnit( void )
{
	return	G_motor_stat.millirad_per_sec;
}


static signed short	calculateCurrent( signed short voltage_millivolt, signed long millirad_per_sec )
{
	return	(voltage_millivolt - millirad_per_sec*RAD_PER_SEC_TO_RND_PER_MIN/KN)*1000/MOTOR_R_MILLIOHM;
}
/****************************************/

/****************************************/
static void	initializeTimer( void )
{
	unsigned int	config;

	config	=	T2_ON & T2_IDLE_STOP & T2_GATE_OFF & T2_PS_1_8 & 
				T2_32BIT_MODE_OFF & T2_SOURCE_INT;

	OpenTimer2( config, 10000 );
	ConfigIntTimer2( T2_INT_PRIOR_3 & T2_INT_ON );
}

/****************************************/


/****************************************/
void _ISR	_T2Interrupt( void )
{
	static long		sum_pulse;
	signed long		old_millirad_per_sec;
	signed short	pulse_per_sample;

	_T2IF	= 0;

	pulse_per_sample	= readCountEncorder();
	setCountEncorder(0);

	/* 位置 */
	sum_pulse	+= pulse_per_sample;
	G_motor_stat.millirad	= sum_pulse * RND_TO_MILLIRAD / ENCODER_PPR;

	/* 速度 */
	old_millirad_per_sec	= G_motor_stat.millirad_per_sec;
	G_motor_stat.millirad_per_sec	= (long)pulse_per_sample * PPS_TO_MRPS;

	/* 加速度 */
	G_motor_stat.millirad_per_sec2	= G_motor_stat.millirad_per_sec - old_millirad_per_sec;

	G_motor_stat.current_milliamp	= calculateCurrent( G_motor_stat.voltage_millivolt, G_motor_stat.millirad_per_sec );


}
/****************************************/
