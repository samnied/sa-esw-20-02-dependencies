#include "../Inc/StackTrace.h"
#include <stdlib.h>

StackTrace::StackTrace()
{
	// disable all interrupts to avoid a corruption of the
	// measurement by an occurrence of an interrupt
}
void StackTrace::start()
{
	if (IAR == 0)	//solution for STMCubeIDE
	{
		clear();
    	StackTrace::stackStartValue = StackTrace::getStackPointer();
    	StackTrace::heapStartValue = StackTrace::getHeapPointer();
    	for (int i = StackTrace::stackStartValue; i >= StackTrace::heapStartValue; i = i-0x4)
        	{
      	 	 //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	 	 volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	 	 UART0CTL = 0xCD;
       	 	}
	}
	else			//solution for IAR
	{
		clear();
		StackTrace::stackStartValue = StackTrace::getStackPointer();
                StackTrace::heapStartValue = StackTrace::getHeapPointer();
		for (int i = StackTrace::IARStackBase; i < StackTrace::stackStartValue - 0xc; i = i + 0x4)
        	{
      	 	 //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	 	 volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	 	 UART0CTL = 0xCD;
       	 	}
		for (int i = StackTrace::IARHeapLimit; i > StackTrace::heapStartValue; i = i - 0x4)
        	{
      	 	 //volatile unsigned int& UART0 = *((volatile unsigned int*)stackB);
      	 	 volatile unsigned int& UART0CTL = *((volatile unsigned int*)i);
      	 	 UART0CTL = 0xCD;
       	 	}
	}
	
}
void StackTrace::stop()
{
  if (IAR == 0)	//solution for STMCubeIDE
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
	else			//solution for IAR
	{
        //for Stack
        volatile unsigned int& UART0 = *((volatile unsigned int*)StackTrace::IARStackBase);	
	for (int i = 0x0000; i <= 0x18000; i = i + 0x1)
        {
        	 volatile unsigned int& UART0CTL = *(&UART0 + i);
        	 unsigned int current;
    		 current = UART0CTL;
        	 if (current != 0xCD)
        	 {
                      StackTrace::stackStopValue = (int)&UART0CTL;
                      break;
        	  }
          }
      //for Heap
      volatile unsigned int& UART1 = *((volatile unsigned int*)StackTrace::IARHeapLimit);
      for (int i = 0x0000; i <= (0x18000); i = i + 0x1)
                {
              	  volatile unsigned int& UART1CTL = *(&UART1 - i);
              	  unsigned int current;
          		  current = UART1CTL;
              	  if (current != 0xCD)
              	  {
              		  StackTrace::heapStopValue = (int)&UART1CTL;
              		  break;
              	  }
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

void StackTrace::setstackB(int i)
{
	StackTrace::stackB = i;
}

void StackTrace::setIARValue(int i)
{
	StackTrace::IAR = i;
}

void StackTrace::setIARStackBase(int i)
{
	StackTrace::IARStackBase = i;
}

void StackTrace::setIARHeapLimit(int i)
{
	StackTrace::IARHeapLimit = i;
}

