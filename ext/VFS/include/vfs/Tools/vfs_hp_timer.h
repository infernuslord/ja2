#ifndef _VFS_HP_TIMER_
#define _VFS_HP_TIMER_

#include <vfs/vfs_config.h>

#ifdef WIN32
	#include <Windows.h>
#elif __linux__
  #include <sys/time.h>
#endif

namespace vfs
{
	class VFS_API HPTimer
	{
	public:
		HPTimer();
		~HPTimer();

		void		startTimer();
		void		stopTimer();
		
		long long	ticks();
		double		running();

		double		getElapsedTimeInSeconds();
	protected:
		bool			is_running;
	#ifdef WIN32
		LARGE_INTEGER	ticksPerSecond;
		LARGE_INTEGER	tick,tick2;
	#elif __linux__
		timeval			t1,t2;
	#endif
	};
}

#endif // _VFS_HP_TIMER_
