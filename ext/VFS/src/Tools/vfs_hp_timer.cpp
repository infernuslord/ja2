#include <vfs/Tools/vfs_hp_timer.h>

vfs::HPTimer::HPTimer() : is_running(false)
{
#ifdef WIN32
	QueryPerformanceFrequency(&ticksPerSecond);
#endif
}

vfs::HPTimer::~HPTimer()
{
}

void vfs::HPTimer::startTimer()
{
#ifdef WIN32
	QueryPerformanceCounter(&tick);
#elif __linux__
	gettimeofday(&t1,0);
#endif
	is_running = true;
}

long long vfs::HPTimer::ticks()
{
	if(is_running)
	{
#ifdef WIN32
		QueryPerformanceCounter(&tick2);
		return tick2.QuadPart - tick.QuadPart;
#elif __linux__
		gettimeofday(&t2,0);
		return t2.tv_usec - t1.tv_usec;
#endif
	}
	return 0;
}
double vfs::HPTimer::running()
{
	if(is_running)
	{
#ifdef WIN32
		QueryPerformanceCounter(&tick2);
		return (double)(tick2.QuadPart - tick.QuadPart)/(double)ticksPerSecond.QuadPart;
#elif __linux__
		gettimeofday(&t2,0);
		return (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
#endif
	}
	return 0;
}

void vfs::HPTimer::stopTimer()
{
#ifdef WIN32
	QueryPerformanceCounter(&tick2);
#elif __linux__
	gettimeofday(&t2,0);
#endif
	is_running = false;
}

double vfs::HPTimer::getElapsedTimeInSeconds()
{
#ifdef WIN32
	return (double)(tick2.QuadPart - tick.QuadPart)/(double)ticksPerSecond.QuadPart;
#elif __linux__
	return (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
#endif
}
