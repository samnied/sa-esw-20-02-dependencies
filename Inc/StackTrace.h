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

private:
	/**
	 * @brief set start value to zero
	 */
	void clear();
	int startValue;
    int stopValue;
};

#endif
