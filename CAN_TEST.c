
/*********************************************************************
**	实验目的:通过外部其他CAN设备给sxd2812发送数据，了解CAN总线的  **
**  设置和通讯过程，请尤其注意ID的设置。                            **
**	实验说明:将MBOX16设置为接收模式，并采用中断的方式接收数据       **
**	实验结果:可以观察变量Rec_h，Rec_l,看看收到的数据                **
****************************************************************/
#include "CAN_TEST.h"

//Uint8 msg_received = 0;


Uint8 canReceive(Message *m)
{
	Uint32 mbdtmp = 0, regtmpnd = 0, Rec_l = 0, Rec_h = 0;
	//Uint8  i = 0, j =0, k = 0;
	Uint16 mbnum = 0;

    volatile struct ECAN_MBOXES *pECanaMboxes;
    volatile struct MBOX *pmbox;

    pECanaMboxes = &ECanaMboxes;
    pmbox = &pECanaMboxes->MBOX0;

	if (msg_received == 0)
	{
		return 0;
	}

	regtmpnd = ECanaRegs.CANRMP.all;
	mbdtmp = ECanaRegs.CANMD.all;
	mbnum = 16;
	while (regtmpnd != 0)
	{
		if ((((regtmpnd >> mbnum) & 0x01) != 0) && (((mbdtmp >> mbnum) & 0x01) == 1))
		{
			break;
		}

		mbnum++;
		if (mbnum >= 32)
		{
			//msg_received = 0;
			break;
		}
	}

	if ((mbnum >= 16) && (mbnum <= 31))
	{
		pmbox += mbnum;
		Rec_l = pmbox->MDL.all;
		Rec_h = pmbox->MDH.all;

		canrxmsg.data[0] = Rec_l & (Uint8)0xFF;
		canrxmsg.data[1] = (Rec_l >> 8) & (Uint8)0xFF;
		canrxmsg.data[2] = (Rec_l >> 16) & (Uint8)0xFF;
		canrxmsg.data[3] = (Rec_l >> 24) & (Uint8)0xFF;
		canrxmsg.data[4] = Rec_h & (Uint8)0xFF;
		canrxmsg.data[5] = (Rec_h >> 8) & (Uint8)0xFF;
		canrxmsg.data[6] = (Rec_h >> 16) & (Uint8)0xFF;
		canrxmsg.data[7] = (Rec_h >> 24) & (Uint8)0xFF;

		if ((pmbox->MSGID.all & (Uint32)0x80000000) != 0)
		{
			canrxmsg.cob_id = pmbox->MSGID.all & ~((Uint32)0xE0000000);
			canrxmsg.extendflag = 1;
		}
		else
		{
			canrxmsg.cob_id = (pmbox->MSGID.all >> 18) & (Uint32)0x7FF;
			canrxmsg.extendflag = 0;
		}
		canrxmsg.len = pmbox->MSGCTRL.bit.DLC;
		canrxmsg.rtr = pmbox->MSGCTRL.bit.RTR;
		//copy data to m and give up extend frame
		if (canrxmsg.extendflag == 0)
		{
			m->cob_id = canrxmsg.cob_id;
			m->rtr = canrxmsg.rtr;
			m->len = canrxmsg.len;
			memcpy(m->data, canrxmsg.data, canrxmsg.len);
		}

		regtmpnd |= ((Uint32)1 << mbnum);
		ECanaRegs.CANRMP.all = regtmpnd;

		msg_received--;
		return 1;
	}
	else
		return 0;
}

Uint8 canSend(CAN_PORT notused, Message *m)
{
	MessageExt temp;
	int i = 0;
	temp.cob_id = m->cob_id;
	temp.rtr = m->rtr;
	temp.len = m->len;

	//memcpy(temp.data, m->data, m->len);
	for (i = 0 ; i < 8 ; i++)
	{
		temp.data[i] =  m->data[i];
	}
	temp.extendflag = 0;

	if (CanTxMsg(temp))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//extern CanState canastate;
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


void CanConfigTxMb(MessageExt *pmsg, int mbnum)
{
    Uint32 datal = 0, datah = 0;
    struct ECAN_REGS ECanaShadow;
    volatile struct ECAN_MBOXES *pECanaMboxes;
    volatile struct MBOX *pmbox;

    volatile Uint32 *pmotoregs;

    pECanaMboxes = &ECanaMboxes;
    pmbox = &pECanaMboxes->MBOX0;
    pmotoregs = &ECanaMOTORegs.MOTO0;



    /*datal = (((Uint32)pmsg->data[3] & 0xFF) << 24) | (((Uint32)pmsg->data[2] & 0xFF) << 16) |
    		   (((Uint32)pmsg->data[1] & 0xFF) << 8) | (pmsg->data[0] & 0xFF);

    datah = (((Uint32)pmsg->data[7] & 0xFF) << 24) | (((Uint32)pmsg->data[6] & 0xFF) << 16) |
    		 (((Uint32)pmsg->data[5] & 0xFF) << 8) | (pmsg->data[4] & 0xFF);*/

    pmbox += mbnum;

    pmbox->MDL.byte.BYTE3 = pmsg->data[0];
    pmbox->MDL.byte.BYTE2 = pmsg->data[1];
    pmbox->MDL.byte.BYTE1 = pmsg->data[2];
    pmbox->MDL.byte.BYTE0 = pmsg->data[3];

    pmbox->MDH.byte.BYTE7 = pmsg->data[4];
    pmbox->MDH.byte.BYTE6 = pmsg->data[5];
    pmbox->MDH.byte.BYTE5 = pmsg->data[6];
    pmbox->MDH.byte.BYTE4 = pmsg->data[7];

    if (pmsg->extendflag == 1)
    {
    	pmbox->MSGID.all = pmsg->cob_id | (Uint32)0x80000000;
    }
    else
    {
    	pmbox->MSGID.all = (pmsg->cob_id << 18) & (Uint32)0x3FFFFFFF;
    }

    //pmbox->MDL.all = datal;
    //pmbox->MDH.all = datah;
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

int CanTxMsg(MessageExt data)
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



//===========================================================================
// No more.
//===========================================================================
