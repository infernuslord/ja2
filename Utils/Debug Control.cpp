#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
#else
	#include "types.h"
	#include "Debug Control.h"
	#include "stdio.h"
#endif

#include <vfs/Core/vfs.h>
#include <vfs/Tools/vfs_log.h>

#ifdef _ANIMSUBSYSTEM_DEBUG

void AnimDbgMessage( CHAR8 *strMessage)
{
	FILE		*OutFile;

	if ((OutFile = fopen("AnimDebug.txt", "a+t")) != NULL)
	{ 
	fprintf(OutFile, "%s\n", strMessage);
		fclose(OutFile);
	}
}

#endif


#ifdef _PHYSICSSUBSYSTEM_DEBUG

void PhysicsDbgMessage( CHAR8 *strMessage)
{
	FILE		*OutFile;

	if ((OutFile = fopen("PhysicsDebug.txt", "a+t")) != NULL)
	{ 
	fprintf(OutFile, "%s\n", strMessage);
		fclose(OutFile);
	}
}

#endif



#ifdef _AISUBSYSTEM_DEBUG

void AiDbgMessage( CHAR8 *strMessage)
{
	FILE		*OutFile;

	if ((OutFile = fopen("AiDebug.txt", "a+t")) != NULL)
	{ 
	fprintf(OutFile, "%s\n", strMessage);
		fclose(OutFile);
	}
}

#endif


void LiveMessage( CHAR8 *strMessage)
{
#ifndef USE_VFS
	FILE		*OutFile;

	if ((OutFile = fopen("Log.txt", "a+t")) != NULL)
	{ 
	fprintf(OutFile, "%s\n", strMessage);
		fclose(OutFile);
	}
#else
	static vfs::Log& liveMsg = *vfs::Log::create(L"LiveLog.txt",true);
	liveMsg << strMessage << vfs::Log::endl;
#endif
}
void MPDebugMsg( CHAR8 *strMessage)
{
#ifndef USE_VFS
	FILE		*OutFile;

	if ((OutFile = fopen("MPDebug.txt", "a+t")) != NULL)
	{ 
	fprintf(OutFile, "%s\n", strMessage);
		fclose(OutFile);
	}
#else
	static vfs::Log& mpMsg = *vfs::Log::create(L"MPDebug.txt", true);
	mpMsg << strMessage << vfs::Log::endl;
#endif
}
