/**************************************/
/*hall.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include <xc.h>
#include "hall.h"
#include "../../../pin_assign.h"

#ifdef	DO_TEST
#include <stdio.h>
#endif


/**************************************/
void initializeHall(void)
{
    INITIALIZE_HALL_1
    INITIALIZE_HALL_2
    INITIALIZE_HALL_3

    _CNIF = 0; /*フラグクリア*/
    _CNIP = 7; /*割り込み優先度*/
    _CNIE = 1; /*割り込み許可*/
}



unsigned char getPhaseHall(unsigned char hall_1, unsigned char hall_2, unsigned char hall_3)
{
    unsigned char phase_conbined;

    phase_conbined = (hall_1 << 2) | (hall_2 << 1) | (hall_3 << 0);

    switch(phase_conbined){
    case 0b101:
        return HALL_PHASE_1;

    case 0b100:
        return HALL_PHASE_2;

    case 0b110:
        return HALL_PHASE_3;

    case 0b010:
        return HALL_PHASE_4;

    case 0b011:
        return HALL_PHASE_5;

    case 0b001:
        return HALL_PHASE_6;

    default:
        return 0xFF;
    }
}


/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST

void Test_getPhase(void)
{
    unsigned char hall_1, hall_2, hall_3;
    unsigned char phase;

    for( hall_1 = 0; hall_1 <= 1; hall_1++ ){
        for( hall_2 = 0; hall_2 <= 1; hall_2++ ){
            for( hall_3 = 0; hall_3 <= 1; hall_3++ ){
                phase	= getPhase( hall_1, hall_2, hall_3 );
                printf( "Input: hall_1=%d,hall_2=%d, hall_3=%d\n", hall_1, hall_2, hall_3 );
                printf( "Output: Phase = %d\n\n", phase );
            }
        }
    }
}


void Test_getFowardPhase(void)
{
    unsigned char phase, f_phase;

    printf("** Test_getFowardPhase **\n\n");

    for( phase = 0; phase < 6; phase++ ){
        f_phase	= getFowardPhase( phase );
        printf("now phase = %d, f_phase = %d\n", phase, f_phase );
    }

    printf("\n");
}


void Test_getBackwardPhase(void)
{
    unsigned char phase, b_phase;

    printf("** Test_getBackwardPhase **\n\n");

    for( phase = 0; phase < 6; phase++ ){
        b_phase	= getBackwardPhase( phase );
        printf("now phase = %d, b_phase = %d\n", phase, b_phase );
    }

    printf("\n");
}

#endif
