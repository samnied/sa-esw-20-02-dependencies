/*
 * StackTrace.h
 *
 *  Created on: 28.10.2020
 *      Author: Marc Benz
 */
#ifndef STACKTRACE_H
#define STACKTRACE_H

 
/**
 * @brief provides the functionality to measure the stacksize
 */
class StackTrace
{
public:
	/**
	 * @brief StackTrace constructor
	 */
	StackTrace();

	/**
	 * @brief measures the stack at this point and therefore starts the measurement
	 */
	void start();

	/**
	 * @brief measures the stack at this point and therefore stops the measurement
	 */
	void stop();

	/**
	 * @brief subtracts the measured start value from the stop value,
	 * returns the result
	 * @return stackutilization measured from start to stop in Bytes 
	 */
	int getStackSizeDifference();

	/**
	 * @brief get current stack size
	 * @return stack size
	 */
	int getCurrentStackSize();

	/**
    * @brief get maximum Stacksize at point you stopped (you also need start)
	* @return max stack size at stop point
	*/
	int getMaxStackSize();

	/**
	 * @brief set stackB
	 */
	void setstackB(int i);

    /**
    * @brief get Heap Pointer
    * @return adress of Heappointer
    */
    int getHeapDifference();

	/**
    * @brief set the IAR value (if IAR is used set to one, else set to 0) (should only be used for bugfixing, will later be done with GDB)
    */
    void setIARValue(int i);

	/**
    * @brief set the IARStackBase value (can be read from .out file)(should only be used for bugfixing, will later be done with GDB)
    */
	void setIARStackBase(int i);

private:
	/**
	 * @brief set start value to zero
	 */
	void clear();

    /**
	 * @brief get Stack Pointer with inline assembly, this function can only be used in get_StackPointer
	 */
    int get_SP(void);

    /**
	 * @brief get Stack Pointer, this function can be used
     * @return adress of Stackpointer
	 */
    int getStackPointer(void);

    /**
    * @brief get Heap Pointer
    * @return adress of Heappointer
    */
    int getHeapPointer(void);

	volatile int IARStackBase;	//volatile ensures that it is not optimised away (because it will be set from the GDB)
	volatile int IAR = 0;		//volatile ensures that it is not optimised away (because it will be set from the GDB)
	int stackStartValue;
	int heapStartValue;
    int stackStopValue;
    int heapStopValue;
	int stackB;
};

#endif
