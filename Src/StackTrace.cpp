#include "../Inc/StackTrace.h"

StackTrace::StackTrace()
{
	// disable all interrupts to avoid a corruption of the
	// measurement by an occurrence of an interrupt
}
void StackTrace::start()
{
	clear();
    StackTrace::startValue = StackTrace::getCurrentStackSize();
    for (int i =(0x20018000 - StackTrace::startValue); i >= stackB; i = i-0x4)
        {
      	  //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	  volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	  UART0CTL = 0xCD;
        }
}
void StackTrace::stop()
{
    volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      for (int i = 0x0000; i <= 0x5fff; i = i + 0x1)
          {
        	  volatile unsigned int& UART0CTL = *(&UART0 + i);
        	  unsigned int current;
    		  current = UART0CTL;
        	  if (current != 0xCD)
        	  {

        		  StackTrace::stopValue = (0x20018000 - stackB) - i;
        		  break;
        	  }
          }
}
void StackTrace::clear()
{
	StackTrace::startValue = 0;
    StackTrace::stopValue = 0;
}
int StackTrace::getStackSizeDifference()
{
	return StackTrace::stopValue - StackTrace::startValue;
}
int StackTrace::getCurrentStackSize()
{
	return 0x20018000 - StackTrace::getStackPointer();
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
