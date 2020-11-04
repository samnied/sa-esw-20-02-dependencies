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
	void setstackB(int a);

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
	int startValue;
    int stopValue;
	int stackB;
};

#endif
