
/*********************************************************************
**	实验目的:通过外部其他CAN设备给sxd2812发送数据，了解CAN总线的  **
**  设置和通讯过程，请尤其注意ID的设置。                            **
**	实验说明:将MBOX16设置为接收模式，并采用中断的方式接收数据       **
**	实验结果:可以观察变量Rec_h，Rec_l,看看收到的数据                **
****************************************************************/

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define MAXCOUNTER (0x70000000)



Uint64 numb;
Uint32 datatmpl;
Uint32 datatmph;

Uint32 CanId;


//extern CanState canastate;

extern void InitECan(void);



int CanFindIdleTxMb()
{
    Uint8 index = 0;
    Uint32 mbflag = 0, mbtaflag = 0;
    Uint16 mblflag = 0, mbltaflag = 0;

    mbflag = ECanaRegs.CANME.all;
    mbtaflag = ECanaRegs.CANTA.all;

    mblflag = mbflag & 0xFFFF;
    mbltaflag = mbtaflag & 0xFFFF;

    while(index < 16)
    {
    	if (((mblflag & 0x01) == 0) && ((mbltaflag & 0x01) == 0))
    	{
    		break;
    	}
    	mblflag = mblflag >> 1;
    	mbltaflag = mbltaflag >> 1;
    	index++;
    }

    if (index >= 16)
    {
    	return -1;
    }
    else
    {
    	return index;
    }
}


void CanConfigTxMb(Message *pmsg, int mbnum)
{
    Uint32 datal = 0, datah = 0;
    struct ECAN_REGS ECanaShadow;
    volatile struct ECAN_MBOXES *pECanaMboxes;
    volatile struct MBOX *pmbox;

    volatile Uint32 *pmotoregs;

    pECanaMboxes = &ECanaMboxes;
    pmbox = &pECanaMboxes->MBOX0;
    pmotoregs = &ECanaMOTORegs.MOTO0;

    datal = ((Uint32)pmsg->data[3] << 24) | ((Uint32)pmsg->data[2] << 16) |
    		   ((Uint32)pmsg->data[1] << 8) | (pmsg->data[0]);

    datah = ((Uint32)pmsg->data[7] << 24) | ((Uint32)pmsg->data[6] << 16) |
    		 ((Uint32)pmsg->data[5] << 8) | (pmsg->data[4]);

    pmbox += mbnum;
    if (pmsg->extendflag == 1)
    {
    	pmbox->MSGID.all = pmsg->cob_id | (Uint32)0x80000000;
    }
    else
    {
    	pmbox->MSGID.all = (pmsg->cob_id << 18) & (Uint32)0x3FFFFFFF;
    }

    pmbox->MDL.all = datal;
    pmbox->MDH.all = datah;
    pmbox->MSGCTRL.bit.DLC = pmsg->len;
    pmbox->MSGCTRL.bit.RTR = pmsg->rtr;

    //config mb as tx_mb
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all &= ~((Uint32)1 << mbnum);
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
    //enable correspond mb
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all |= ((Uint32)1 << mbnum);
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	//tx the message;
	ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
	ECanaShadow.CANTRS.all |= ((Uint32)1 << mbnum);
	ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
	//config tx timeout
	pmotoregs += mbnum;
	*pmotoregs = ECanaRegs.CANTSC + 100000;
	ECanaShadow.CANTOC.all |= ((Uint32)1 << mbnum);
	ECanaRegs.CANTOC.all = ECanaShadow.CANTOC.all;
}

int CanTxMsg(Message data)
{
    int result = 0;
    //find free mailbox for tx;
    result = CanFindIdleTxMb();
    //judge the mb by the result
    if ((result < 0) || (result >= 16))
    {
    	return -1;
    }
    //config mb for tx
    else
    {
    	CanConfigTxMb(&data, result);
    	return 1;
    }
}

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
	Message msg;

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

interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   if (CpuTimer0.InterruptCount > MAXCOUNTER)
   {
	   CpuTimer0.InterruptCount = 0;
   }
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
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
    for(;;)
	{
		//ECanaRegs.CANTRS.all = 0x00000001;
		//while(ECanaRegs.CANTA.all == 0)
		//{

		//}
		//ECanaMboxes.MBOX0.MDL.all = datatmpl;
		//ECanaMboxes.MBOX0.MDH.all = datatmph;
		//ECanaRegs.CANTRS.all = 0x00000001;
		//ECanaMboxes.MBOX0.MDL.all = 0x01020304;
		//ECanaMboxes.MBOX0.MDH.all = 0x05060708;
		//numb++;
		//datatmpl += 2;
		//datatmph += 2;
    	///////////////////////////////////////////
    	//CanTxTest();
    	CanTest2();
    	///////////////////////////////////////////
		//ECanaRegs.CANTRS.all = 0x00000001;
		//while(ECanaRegs.CANTA.all == 0);
		//ECanaRegs.CANTA.all = 0x00000001;
		//MessageSendCount++;				//在这里设断点，观察
		//ECanaMboxes.MBOX0.MDL.all = 0x01234567;
		//ECanaMboxes.MBOX0.MDH.all = 0x89ABCDEF;
	}

}

//===========================================================================
// No more.
//===========================================================================
