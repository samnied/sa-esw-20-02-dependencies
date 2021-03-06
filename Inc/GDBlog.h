/*
 * GDBlog.h
 *
 *  Created on: 08.11.2020
 *      Author: Samuel Niederer
 */
#ifndef GDBLOG_H
#define GDBLOG_H

/**
 * @brief provides a container for measurement data, which can be read by GDB
 */
class GDBlog
{
public:
	enum Type{time, stack, heap};

	/**
	 * @brief GDBlog constructor
	 */
	GDBlog();

	/**
	 * @brief stores val to an internal array
	 * @param val value to log
	 * @param t type of data (time, stack, heap)
	 */
	void log(int val, Type t);

	/**
	 * @brief works as a mark for GDB to break
	 * call this function at the end of the measurement
	 */
	void end();

private:
	enum{size = 100};

	volatile int tBuff[size];
	volatile int sBuff[size];
	volatile int hBuff[size];

	volatile int tIndex;
	volatile int sIndex;
	volatile int hIndex;

	volatile int i;
};

#endif
