#include "../Inc/StackTrace.h"

StackTrace::StackTrace()
{
	// disable all interrupts to avoid a corruption of the
	// measurement by an occurrence of an interrupt
}
void StackTrace::start()
{
	clear();
    StackTrace::stackStartValue = StackTrace::getCurrentStackSize();
    for (int i =(0x20018000 - StackTrace::stackStartValue); i >= stackB; i = i-0x4)
        {
      	  //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	  volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	  UART0CTL = 0xCD;
        }
}
void StackTrace::stop()
{
    volatile unsigned int& UART0 = *((volatile unsigned int*)0x2000c000);
      for (int i = 0x0000; i <= 0xc000; i = i + 0x1)
          {
        	  volatile unsigned int& UART0CTL = *(&UART0 + i);
        	  unsigned int current;
    		  current = UART0CTL;
        	  if (current != 0xCD)
        	  {
        		  StackTrace::stackStopValue = (0x20018000 - 0x2000c000) - 4 * i;
        		  break;
        	  }
          }
}

void StackTrace::clear()
{
	StackTrace::stackStartValue = 0;
    StackTrace::stackStopValue = 0;
    StackTrace::heapStopValue = 0;
}

int StackTrace::getStackSizeDifference()
{
	return StackTrace::stackStopValue - StackTrace::StackStartValue;
}

int StackTrace::getCurrentStackSize()
{
	return 0x20018000 - StackTrace::getStackPointer();
}

int StackTrace::getMaxStackSize()
{
	return StackTrace::stackStopValue;
}

int StackTrace::get_SP()
{
	asm( "MOV R3, SP" );
}

int StackTrace::getStackPointer()
{
    int a = StackTrace::get_SP();
}

void StackTrace::setstackB(int a)
{
	stackB = a;
}
