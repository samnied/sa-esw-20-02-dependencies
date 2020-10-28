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
    for (int i = StackTrace::startValue - 0x20000ae0; i >= 0x0; i = i-0x1)
        {
      	  volatile unsigned int& UART0 = *((volatile unsigned int*)0x20000ae0);
      	  volatile unsigned int& UART0CTL = *(&UART0 + i);
      	  UART0CTL = 0xCD;
        }
}
void StackTrace::stop()
{
    volatile unsigned int& UART0 = *((volatile unsigned int*)0x20000ae0);
      for (int i = 0x0000; i <= 0x5fff; i = i + 0x1)
          {
        	  volatile unsigned int& UART0CTL = *(&UART0 + i);
        	  unsigned int current;
    		  current = UART0CTL;
        	  if (current != 0xCD)
        	  {

        		  StackTrace::stopValue = (0x20018000 - 0x20000ae0) - i;
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