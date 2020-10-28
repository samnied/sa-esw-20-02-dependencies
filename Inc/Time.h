#ifndef TIME_H
#define TIME_H
 
class Time
{
public:
	Time();
	void start();
	void stop();
	uint32_t read();
	uint32_t getOffset();

private:
	void enableDWT();
	void clear();
	uint32_t offset;
};

#endif