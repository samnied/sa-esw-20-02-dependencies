#include "../Inc/StackTrace.h"
#include <stdlib.h>

StackTrace::StackTrace()
{
	// disable all interrupts to avoid a corruption of the
	// measurement by an occurrence of an interrupt
}
void StackTrace::start()
{
	clear();
    StackTrace::stackStartValue = StackTrace::getCurrentStackSize();
    StackTrace::heapStartValue = StackTrace::getHeapPointer();
    for (int i =(0x20018000 - (StackTrace::stackStartValue + 0)); i >= StackTrace::heapStartValue; i = i-0x4)
        {
      	  //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	  volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	  UART0CTL = 0xCD;
        }
}
void StackTrace::stop()
{
    volatile unsigned int& UART0 = *((volatile unsigned int*)0x2000c000);
    //for Stack
      for (int i = 0x0000; i <= (0xc000 - StackTrace::stackStartValue); i = i + 0x1)
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
      //for Heap
      for (int i = 0x0000; i <= (0xc000); i = i + 0x1)
                {
              	  volatile unsigned int& UART0CTL = *(&UART0 - i);
              	  unsigned int current;
          		  current = UART0CTL;
              	  if (current != 0xCD)
              	  {
              		  StackTrace::heapStopValue = (0x2000c000 - 4 * i);
              		  break;
              	  }
                }
}

void StackTrace::clear()
{
	StackTrace::stackStartValue = 0;
	StackTrace::heapStartValue = 0;
    StackTrace::stackStopValue = 0;
    StackTrace::heapStopValue = 0;
}

int StackTrace::getHeapDifference()
{
	return StackTrace::heapStopValue - StackTrace::heapStartValue + 4;
}

int StackTrace::getStackSizeDifference()
{
	return StackTrace::stackStopValue - StackTrace::stackStartValue;
}

int StackTrace::getCurrentStackSize()
{
	return 0x20018000 - StackTrace::getStackPointer();
}

int StackTrace::getMaxStackSize()
{
	return StackTrace::stackStopValue;
}

int StackTrace::getHeapPointer(void)
{
	void* a = malloc(sizeof(int));
	free (a);
	return (int)a;
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
