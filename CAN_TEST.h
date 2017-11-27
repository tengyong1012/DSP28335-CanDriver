/*
 * CAN_TEST.h
 *
 *  Created on: 2017Äê11ÔÂ27ÈÕ
 *      Author: Wiiboox
 */

#ifndef CAN_TEST_H_
#define CAN_TEST_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "timers_driver.h"
#include "canfestival.h"


extern Uint8 msg_received;

extern void InitECan(void);
extern int CanTxMsg(MessageExt data);
extern Uint8 canReceive(Message *m);

#endif /* CAN_TEST_H_ */
