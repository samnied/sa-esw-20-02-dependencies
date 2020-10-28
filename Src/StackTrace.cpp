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
}
void StackTrace::stop()
{
	StackTrace::stopValue = StackTrace::getCurrentStackSize();
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
	return 0;
}
