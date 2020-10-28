#include "Time.h"
Time::Time()
{
	// disable all interrupts to avoid a corruption of the
	// measurement by an occurrence of an interrupt
	__disable_irq();
	enableDWT();
	start();
	stop();
	offset = read();
	__enable_irq();
}
void Time::start()
{
	clear();
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
void Time::stop()
{
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
}
void Time::clear()
{
	DWT->CYCCNT = 0;
}
uint32_t Time::read()
{
	return DWT->CYCCNT - offset;
}
uint32_t Time::getOffset()
{
	return offset;
}
void Time::enableDWT()
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
}
