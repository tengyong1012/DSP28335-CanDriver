/*
 * 28335timerdriver.c
 *
 *  Created on: 2017Äê11ÔÂ27ÈÕ
 *      Author: Wiiboox
 */

// Includes for the Canfestival driver
#include "canfestival.h"
#include "timer.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

// Define the timer registers
#define TimerAlarm (CpuTimer0.InterruptCount)
#define TimerCounter (CpuTimer0.InterruptCount)
#define MAXCOUNTER (0x70000000)
/************************** Modul variables **********************************/
// Store the last timer value to calculate the elapsed time
static TIMEVAL last_time_set = TIMEVAL_MAX;
/******************************************************************************
Initializes the timer, turn on the interrupt and put the interrupt time to zero
INPUT	void
OUTPUT	void
******************************************************************************/
void initTimer(void)
{
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 150, 1000);
	CpuTimer0Regs.TCR.all = 0x4001;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	IER |= M_INT1;
}

/******************************************************************************
Set the timer for the next alarm.
INPUT	value TIMEVAL (unsigned long)
OUTPUT	void
******************************************************************************/
void setTimer(TIMEVAL value)

{
  TimerAlarm += (int)value;	// Add the desired time to timer interrupt time
}

/******************************************************************************
Return the elapsed time to tell the Stack how much time is spent since last call.
INPUT	void
OUTPUT	value TIMEVAL (unsigned long) the elapsed time
******************************************************************************/
TIMEVAL getElapsedTime(void)
{
  unsigned int timer = TimerCounter;            // Copy the value of the running timer
  if (timer > last_time_set)                    // In case the timer value is higher than the last time.
    return (timer - last_time_set);             // Calculate the time difference
  else if (timer < last_time_set)
    return (last_time_set - timer);             // Calculate the time difference
  else
    return TIMEVAL_MAX;
}

interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   last_time_set = TimerCounter;
   if (CpuTimer0.InterruptCount > MAXCOUNTER)
   {
	   CpuTimer0.InterruptCount = 0;
   }
   TimeDispatch();
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/*#ifdef  __IAR_SYSTEMS_ICC__
#pragma type_attribute = __interrupt
#pragma vector=TIMER3_COMPB_vect
void TIMER3_COMPB_interrupt(void)
#else	// GCC
ISR(TIMER3_COMPB_vect)
#endif	// GCC*/
/******************************************************************************
Interruptserviceroutine Timer 3 Compare B for the CAN timer
******************************************************************************/
/*{
  last_time_set = TimerCounter;
  TimeDispatch();                               // Call the time handler of the stack to adapt the elapsed time
}*/
