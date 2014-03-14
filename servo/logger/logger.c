/*
 * File:   logger.c
 * Author: Master
 *
 * Created on 2013/05/01 11:55
 */


#include	"logger.h"
#include	<fifo/fifo.h>

#define	_DEBUG
#include	<assert/assert.h>

/* **************************** */
FIFO	G_log_ref, G_log_mes;
/* **************************** */

/* **************************** */
extern void initLogger( void )
{
	initializeFIFO( &G_log_ref );
	initializeFIFO( &G_log_mes );
}
/* **************************** */



/* **************************** */
ErrSetLogger	setLogger( signed char ref_speed, signed char mesured_speed )
{
	ErrAddFIFO	err_1, err_2;
	
	err_1	= addFIFO( &G_log_ref, ref_speed );
	err_2	= addFIFO( &G_log_mes, mesured_speed );

	if( (err_1 == FIFO_OVERFLOWED) || (err_2 == FIFO_OVERFLOWED) ){
		return	LOG_OVERFLOWED;
	}else{
		return	SUCCESS_SETLOG;
	}
}


ErrGetLogger	getLogger( signed char* ref_speed, signed char* mesured_speed )
{
	ErrGetFIFO	err_1, err_2;

	err_1	= getFIFO( &G_log_ref, (fifo_type*)ref_speed );
	err_2	= getFIFO( &G_log_mes, (fifo_type*)mesured_speed );

	if( (err_1 == FIFO_EMPTY) || (err_2 == FIFO_EMPTY) ){
		return	LOG_EMPTY;
	}else{
		return	SUCCESS_GETLOG;
	}
}

extern int	getAllLogger( signed char* ref_speed, signed char* mesured_speed, unsigned short* num_of_data )
{

	/*TODO::FIFO Ver 2.0の仕様で書き直す*/
	ErrGetAllFIFO	err_1, err_2;

	err_1	= getAllFIFO( &G_log_ref, (fifo_type*)ref_speed, 32, num_of_data );
	err_2	= getAllFIFO( &G_log_mes, (fifo_type*)mesured_speed, 32, num_of_data );

	if( (err_1 == BUFFER_SIZE_IS_NOT_ENOUGH) || (err_2 == BUFFER_SIZE_IS_NOT_ENOUGH) ){
		return	1;
	}

	return	0;


}
/* **************************** */

