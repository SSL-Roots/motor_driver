
/*
 * File:   encorder.h
 * Author: Master
 *
 * Created on 2013/04/04 19:28
 */

#ifndef	_ENCORDER_H_
#define	_ENCORDER_H_

#define	ENCODER_PPR	1440//4996
/***************************************/

extern void	initializeEncorder( void );
extern signed int	readCountEncorder( void );
extern void	setCountEncorder( signed int count );

/***************************************/

#endif	/*_ENCORDER_H_*/
