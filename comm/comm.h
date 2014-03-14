/****************************************/
/*comm.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_COMM_H_
#define	_COMM_H_


/****************************************/
//#define	_DEBUG
/****************************************/


/****************************************/
//#define	COMM_MODE_UART
#define	COMM_MODE_I2C

#define	UART_BAUDRATE	57600
#define	I2C_ID	20
/****************************************/

/****************************************/
#define	MAX_DATA	10

#define	COMMAND_NULL			0x00
#define	COMMAND_SPEED_OPENLOOP	0x03
#define	COMMAND_SPEED_PID		0x04
#define	COMMAND_PID_GAIN		0x10

typedef struct	Order{
	unsigned char	command;
	signed int 	data[MAX_DATA];
}Order;
/****************************************/


/****************************************/
void	initializeComm( void );
Order	fetchOrder( void );
short	sendLogs(unsigned short num_data, signed char* ref, signed char* mes);
/****************************************/



/****************************************/
/*テストコード*/
#ifdef	_DEBUG
void	Test_fetchOrder( void );
#endif
/****************************************/

#endif	/*_COMM_H_*/
