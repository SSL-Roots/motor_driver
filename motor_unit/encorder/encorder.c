/*
 * File:   encorder.c
 * Author: Master
 *
 * Created on 2013/04/04 19:28
 */

#include	<qei.h>
#include	<xc.h>
#include	"encorder.h"
#include	"../../pin_assign.h"

/****************************************/
#define	setQEIPortInput(rp_a, rp_b)	_TRISB##rp_a = 1; _TRISB##rp_b = 1
/****************************************/


/****************************************/
static unsigned int	setQEIPort( unsigned char pin_a, unsigned char pin_b );
/****************************************/



/****************************************/
extern void	initializeEncorder( void )
{
	unsigned int	config_1, config_2;

	config_1 =	QEI_DIR_SEL_QEB	& QEI_INT_CLK & QEI_INDEX_RESET_DISABLE &
				QEI_CLK_PRESCALE_1 & QEI_GATED_ACC_DISABLE &
				QEI_LOGIC_CONTROL_IO & QEI_INPUTS_NOSWAP & QEI_MODE_x4_MATCH &
				QEI_UP_COUNT & QEI_IDLE_STOP;
				 
	config_2 =	MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW & 
				POS_CNT_ERR_INT_DISABLE & QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_DISABLE;
	RPINR14	= setQEIPort( 5, 6 );
	setQEIPortInput( 5, 6 );

	OpenQEI( config_1, config_2 );
	setCountEncorder( 0 );
}


static unsigned int	setQEIPort( unsigned char pin_a, unsigned char pin_b )
{
	unsigned int	temp_rpinr14;

	temp_rpinr14	= pin_b;
	temp_rpinr14	&= 0x00FF;
	temp_rpinr14	<<= 8;
	temp_rpinr14	|= (0x00FF & pin_a);

	return	temp_rpinr14;
}
/****************************************/


/****************************************/
extern signed int	readCountEncorder( void )
{
	return	(signed int)((signed long)ReadQEI() - 32768);

}


extern void	setCountEncorder( signed int count )
{
	POSCNT	= (unsigned int)((signed long)count + 32768);
}
/****************************************/
