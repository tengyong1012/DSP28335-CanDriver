/****************************************************************************
*
*文件名：DSP28_ECan.c
*
*功  能：SXDEMBED
*
****************************************************************************/

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/****************************************************************************
*
*名    称：InitECan()
*
*功    能：初始化ECan模块
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitECan(void)
{   
	struct ECAN_REGS ECanaShadow;
	
	//配置GPIO引脚工作在eCAN功能
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	    // Enable pull-up for GPIO18 (CANRXA)

		//	GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;	    // Enable pull-up for GPIO31 (CANTXA)
		GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	    // Enable pull-up for GPIO19 (CANTXA)

	/* Set qualification for selected CAN pins to asynch only */
	// Inputs are synchronized to SYSCLKOUT by default.
	// This will select asynch (no qualification) for the selected pins.

		//   GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;   // Asynch qual for GPIO30 (CANRXA)
	  GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;   // Asynch qual for GPIO18 (CANRXA)


	/* Configure eCAN-A pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be eCAN functional pins.

	  //	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;	// Configure GPIO30 for CANRXA operation
	  GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;	// Configure GPIO18 for CANRXA operation
	  //	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;	// Configure GPIO31 for CANTXA operation
	  GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;
	
	//配置eCAN的RX和TX分别为eCAN的接收和发送引脚
	ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
	ECanaShadow.CANTIOC.bit.TXFUNC = 1;
	ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;
	
	ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
	ECanaShadow.CANRIOC.bit.RXFUNC = 1;
	ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;
	EDIS;
	
	
	EALLOW;
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	//工作在非测试模式
	ECanaShadow.CANMC.bit.STM = 0;
	//工作在ecan模式
	ECanaShadow.CANMC.bit.SCB = 1;
	//least send first
	ECanaShadow.CANMC.bit.DBO = 1;

	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	EDIS;
	
	//初始化所有主设备控制区域为0，控制区域所有的位都初始化为0
	ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
	ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;

	//清除所有的TA位
	ECanaRegs.CANTA.all = 0xFFFFFFFF;
   
   	//清除所有的RMP位
	ECanaRegs.CANRMP.all = 0xFFFFFFFF;
	
	//清除所有的中断标志位
	ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF1.all = 0xFFFFFFFF;
	
	//配置时钟参数
	EALLOW;
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 1;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	EDIS;
    //CPU请求向CANBTC和CANGAM写配置信息，该位置1后必须等到CANED.CCE为1，才能
	//对CANBTC进行操作。
	do
	{
	  ECanaShadow.CANES.all = ECanaRegs.CANES.all;
	}
	while(ECanaShadow.CANES.bit.CCE != 1);
	
	EALLOW;
	//(BRPREG+1)=10 ，CAN时钟为15MHz
	ECanaShadow.CANBTC.bit.BRPREG = 9;
	//CAN通信的波特率为1MHz
	ECanaShadow.CANBTC.bit.TSEG2REG = 2;
	ECanaShadow.CANBTC.bit.TSEG1REG = 10;
	ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;
	
	//CPU请求正常操作
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.bit.CCR = 0;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	EDIS;
	do
	{
	  ECanaShadow.CANES.all = ECanaRegs.CANES.all;
	}
	while(ECanaShadow.CANES.bit.CCE != 0);
	
	//屏蔽所有邮箱，在写MSGID之前要完成该操作
	ECanaRegs.CANME.all = 0;
	
    //设置接收邮箱的ID，扩展帧
	ECanaMboxes.MBOX16.MSGID.all =  0x80C20000;
	///////////////////////////////////////////
	ECanaMboxes.MBOX17.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX18.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX19.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX20.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX21.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX22.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX23.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX24.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX25.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX26.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX27.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX28.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX29.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX30.MSGID.all =  0x80C20000;
	ECanaMboxes.MBOX31.MSGID.all =  0x80C20000;



	///////////////////////////////////////////
	ECanaMboxes.MBOX0.MSGID.all  =  0x80C80000;

	//ECanaMboxes.MBOX16.MSGID.all =  0x00C20000;
	//ECanaMboxes.MBOX0.MSGID.all  =  0x00C80000;
	//设置邮箱16为接收邮箱
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD16 = 1;
    ///////////////////////////////////////////
    ECanaShadow.CANMD.bit.MD17 = 1;
    ECanaShadow.CANMD.bit.MD18 = 1;
    ECanaShadow.CANMD.bit.MD19 = 1;
    ECanaShadow.CANMD.bit.MD20 = 1;
    ECanaShadow.CANMD.bit.MD21 = 1;
    ECanaShadow.CANMD.bit.MD22 = 1;
    ECanaShadow.CANMD.bit.MD23 = 1;
    ECanaShadow.CANMD.bit.MD24 = 1;
    ECanaShadow.CANMD.bit.MD25 = 1;
    ECanaShadow.CANMD.bit.MD26 = 1;
    ECanaShadow.CANMD.bit.MD27 = 1;
    ECanaShadow.CANMD.bit.MD28 = 1;
    ECanaShadow.CANMD.bit.MD29 = 1;
    ECanaShadow.CANMD.bit.MD30 = 1;
    ECanaShadow.CANMD.bit.MD31 = 1;

    ///////////////////////////////////////////
    ECanaShadow.CANMD.bit.MD0  = 0;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
	
	//数据长度 8个BYTE
	ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;
	///////////////////////////////////////////
	ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX22.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX23.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX24.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX26.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX27.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX28.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX29.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX30.MSGCTRL.bit.DLC = 8;
	ECanaMboxes.MBOX31.MSGCTRL.bit.DLC = 8;


	///////////////////////////////////////////
	ECanaMboxes.MBOX0.MSGCTRL.bit.DLC  = 8;
	//没有远方应答帧被请求*/
	ECanaMboxes.MBOX16.MSGCTRL.bit.RTR = 0;
	//////////////////////////////////////////
	ECanaMboxes.MBOX17.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX18.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX19.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX20.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX21.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX22.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX23.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX24.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX25.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX26.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX27.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX28.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX29.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX30.MSGCTRL.bit.RTR = 0;
	ECanaMboxes.MBOX31.MSGCTRL.bit.RTR = 0;

	//////////////////////////////////////////
	ECanaMboxes.MBOX0.MSGCTRL.bit.RTR  = 0;
	//AME enable for mailbox16
	ECanaMboxes.MBOX16.MSGID.bit.AME = 1;
	//////////////////////////////////////////
	ECanaMboxes.MBOX17.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX18.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX19.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX20.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX21.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX22.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX23.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX24.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX25.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX26.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX27.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX28.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX29.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX30.MSGID.bit.AME = 1;
	ECanaMboxes.MBOX31.MSGID.bit.AME = 1;
	/////////////////////////////////////////
	//ECanaRegs.CANGAM.bit.AMI=1;                                //标准帧和扩展帧都可以接收
	//ECanaRegs.CANGAM.bit.GAM150 = 0xffff;
	//ECanaRegs.CANGAM.bit.GAM2816 = 0xffff;
	//ECanaLAMRegs.LAM16.bit.LAMI = 1;
	ECanaLAMRegs.LAM16.all = 0xFFFFFFFF;
	/////////////////////////////////////////
	ECanaLAMRegs.LAM17.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM18.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM19.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM20.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM21.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM22.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM23.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM24.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM25.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM26.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM27.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM28.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM29.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM30.all = 0xFFFFFFFF;
	ECanaLAMRegs.LAM31.all = 0xFFFFFFFF;

	//set opc flag
	ECanaShadow.CANOPC.all = ECanaRegs.CANOPC.all;
	ECanaShadow.CANOPC.bit.OPC16 = 1;
	ECanaShadow.CANOPC.bit.OPC17 = 1;
	ECanaShadow.CANOPC.bit.OPC18 = 1;
	ECanaShadow.CANOPC.bit.OPC19 = 1;
	ECanaShadow.CANOPC.bit.OPC20 = 1;
	ECanaShadow.CANOPC.bit.OPC21 = 1;
	ECanaShadow.CANOPC.bit.OPC22 = 1;
	ECanaShadow.CANOPC.bit.OPC23 = 1;
	ECanaShadow.CANOPC.bit.OPC24 = 1;
	ECanaShadow.CANOPC.bit.OPC25 = 1;
	ECanaShadow.CANOPC.bit.OPC26 = 1;
	ECanaShadow.CANOPC.bit.OPC27 = 1;
	ECanaShadow.CANOPC.bit.OPC28 = 1;
	ECanaShadow.CANOPC.bit.OPC29 = 1;
	ECanaShadow.CANOPC.bit.OPC30 = 1;
	ECanaShadow.CANOPC.bit.OPC31 = 1;
	ECanaRegs.CANOPC.all = ECanaShadow.CANOPC.all;
	/////////////////////////////////////////
	//邮箱使能
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;

	//ECanaShadow.CANME.bit.ME0 =1;
	ECanaShadow.CANME.bit.ME16 =1;
	///////////////////////////////////////////
	ECanaShadow.CANME.bit.ME17 =1;
	ECanaShadow.CANME.bit.ME18 =1;
	ECanaShadow.CANME.bit.ME19 =1;
	ECanaShadow.CANME.bit.ME20 =1;
	ECanaShadow.CANME.bit.ME21 =1;
	ECanaShadow.CANME.bit.ME22 =1;
	ECanaShadow.CANME.bit.ME23 =1;
	ECanaShadow.CANME.bit.ME24 =1;
	ECanaShadow.CANME.bit.ME25 =1;
	ECanaShadow.CANME.bit.ME26 =1;
	ECanaShadow.CANME.bit.ME27 =1;
	ECanaShadow.CANME.bit.ME28 =1;
	ECanaShadow.CANME.bit.ME29 =1;
	ECanaShadow.CANME.bit.ME30 =1;
	ECanaShadow.CANME.bit.ME31 =1;
	///////////////////////////////////////////
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	
	//邮箱中断使能
    EALLOW;
    ECanaRegs.CANMIM.all = 0xFFFFFFFF;
    //ECanaRegs.CANMIM.all = 0x0010FFFF;

    //邮箱中断将产生在ECAN0INT
    ECanaRegs.CANMIL.all = 0;
    ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
    //ECAN0INT中断请求线被使能
    ECanaRegs.CANGIM.bit.I0EN = 1;
    //ECanaRegs.CANGIM.all = 0xFFFFFFFF;
    EDIS;
 

}	

//===========================================================================
// No more.
//===========================================================================
