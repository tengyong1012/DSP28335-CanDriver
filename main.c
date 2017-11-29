/*
 * main.c
 *
 *  Created on: 2017年11月27日
 *      Author: Wiiboox
 */
#include "CAN_TEST.h"
#include "ObjDict.h"
#include "Can.h"

Uint64 numb;
Uint32 datatmpl;
Uint32 datatmph;
Uint32 CanId = 1;

static Message m = Message_Initializer;		// contain a CAN message
void CanTest2()
{
	if (flag == 1)
	{
		CanTxMsg(canrxmsg);
		flag = 0;
	}
}
void CanTxTest(void)
{
	Uint32 datatmpl = 0, datatmph = 0;
	MessageExt msg;

	datatmph = numb >> 32;
	datatmpl = numb & 0xFFFFFFFF;
    //extend frame
	msg.cob_id = (Uint32)0x80000000 | CanId;
	msg.rtr = 0;
	msg.len = 8;
	msg.data[0] = datatmpl & 0xFF;
	msg.data[1] = (datatmpl >> 8) & 0xFF;
	msg.data[2] = (datatmpl >> 16) & 0xFF;
	msg.data[3] = (datatmpl >> 24) & 0xFF;
	msg.data[4] = datatmph & 0xFF;
	msg.data[5] = (datatmph >> 8) & 0xFF;
	msg.data[6] = (datatmph >> 16) & 0xFF;
	msg.data[7] = (datatmph >> 24) & 0xFF;
    //senddata
	if (CanTxMsg(msg) > 0)
	{
		numb++;
		CanId++;
		if (CanId > (Uint32)0x1FFFFFFF)
		{
			CanId = 0;
		}
	}

	if (canastate == BUSOFF)
	{
		InitECan();
		canastate = WORKED;
	}
}



void main(void)
{

	numb = 1;
	CanId = 1;
	datatmpl = 0;
	datatmph = 1;
	canastate = IDEL;
	/*初始化系统*/
	InitSysCtrl();

	/*关中断*/
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	/*初始化PIE中断*/
	InitPieCtrl();

	/*初始化PIE中断矢量表*/
	InitPieVectTable();
	/*time1 for interrupt*/
	EALLOW;
	PieVectTable.TINT0 = &cpu_timer0_isr;
	EDIS;
	InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000);
	CpuTimer0Regs.TCR.all = 0x4001;
	/*初始化SCIA寄存器*/
    InitECan();
    canastate = INITED;
    flag = 0;
    //使能PIE中断
    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	//使能CPU中断
	IER |= M_INT9;
	IER |= M_INT1;
	//PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	EINT;   //开全局中断
	ERTM;	//开实时中断
	canastate = WORKED;

	setNodeId (&ObjDict_Data, CanId);
	setState(&ObjDict_Data, Initialisation);	// Init the state
    for(;;)
	{
        if (canReceive(&m))			// a message reveived
            canDispatch(&ObjDict_Data, &m);         // process it
	}

}

