#ifndef _RFID_H
#define _RFID_H

#include "sys.h"

void uart_send_mydata(u8 *data,u8 len);
void uart_receive_mydata(u8 *data,u8 *len);

u8 RFID_READ(u8 *uid,u8 *block);
u8 RFID_Init(void);
u8 RFID_Disableantenna(void);
u8 GET_UID(u8 *uid);



#endif