/**************************************/
/*hall.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#ifndef	_HALL_H_
#define	_HALL_H_


/**************************************/
/*#define	DO_TEST*/
/**************************************/

/**************************************/

/**************************************/
#define	NUM_PHASE	6
/**************************************/


/**************************************/
#define	HALL_PHASE_1	1
#define	HALL_PHASE_2	2
#define	HALL_PHASE_3	3
#define	HALL_PHASE_4	4
#define	HALL_PHASE_5	5
#define	HALL_PHASE_6	6
/**************************************/


/**************************************/
void	initializeHall( void );

unsigned char	getPhaseHall( unsigned char hall_1, unsigned char hall_2, unsigned char hall_3 );

/**************************************/



/**************************************/
#ifdef	DO_TEST

void	Test_getPhase( void );
/*void	Test_getFowardPhase( void );*/
/*void	Test_getBackwardPhase( void );*/

#endif
/**************************************/

#endif	/*_HALL_H_*/
