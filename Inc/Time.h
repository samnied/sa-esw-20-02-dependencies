/*
 * Time.h
 *
 *  Created on: 28.10.2020
 *      Author: Samuel Niederer
 */
#ifndef TIME_H
#define TIME_H

#include <stdint.h>
 
/**
 * @brief provides the functionality to measure the execution time of code
 */
class Time
{
public:
	/**
	 * @brief Time constructor
	 */
	Time();

	/**
	 * @brief starts the cycle counter
	 */
	void start();

	/**
	 * @brief stops the cycle counter
	 */
	void stop();

	/**
	 * @brief subtracts the measured offset from the cycle counter,
	 * returns the result
	 * @return execution time in cycles
	 */
	uint32_t read();

	/**
	 * @brief get measured offset
	 * @return offset
	 */
	uint32_t getOffset();

private:
	/**
	 * @brief enable Data Watchpoint and Trace(DWT) unit
	 */
	void enableDWT();

	/**
	 * @brief set cycle counter to zero
	 */
	void clear();
	uint32_t offset = 0;
};

#endif
