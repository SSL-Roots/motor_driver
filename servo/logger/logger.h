/*
 * File:   logger.h
 * Author: Master
 *
 * Created on 2013/05/01 11:56
 */

#ifndef	_LOGGER_H_
#define	_LOGGER_H_

/*******************************************/
extern void initLogger( void );

typedef enum ErrSetLogger {
	SUCCESS_SETLOG,
	LOG_OVERFLOWED
} ErrSetLogger;
ErrSetLogger	setLogger( signed char ref_speed, signed char mesured_speed );

typedef enum ErrGetLogger {
	SUCCESS_GETLOG,
	LOG_EMPTY
} ErrGetLogger;
ErrGetLogger	getLogger( signed char* ref_speed, signed char* mesured_speed );

extern int	getAllLogger( signed char* ref_speed, signed char* mesured_speed, unsigned short* num_of_data );
/*******************************************/

#endif	/*_LOGGER_H_*/
