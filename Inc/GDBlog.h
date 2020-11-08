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
	 * @brief starts the cycle counter
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

	int tBuff[size];
	int sBuff[size];
	int hBuff[size];

	int tIndex;
	int sIndex;
	int hIndex;

	volatile int i;
};

#endif
