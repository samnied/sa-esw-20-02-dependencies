#include "../Inc/GDBlog.h"

GDBlog::GDBlog():tIndex(0), sIndex(0), hIndex(0)
{}

void GDBlog::log(int val, Type t)
{
	switch(t)
	{
		case time:
			if(tIndex < size)
			{
				tBuff[tIndex] = val;
				tIndex ++;
			}
		break;
		case stack:
			if(sIndex < size)
			{
				sBuff[sIndex] = val;
				sIndex ++;
			}
		break;
		case heap:
			if(hIndex < size)
			{
				hBuff[hIndex] = val;
				hIndex ++;
			}
		break;
	}
}
void GDBlog::end()
{
	// this operation prevents the compiler
	// from optimizing the function away
	i = 0;
}

