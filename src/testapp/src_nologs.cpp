/**
 * \file 
 * Sample file illustrating selectively disabling the logs from
 * appearing , from a source file.
 * */
#include <liblogger/liblogger_levels.h>
// For this file, we disable all the logs. - NO LOGS FROM THIS FILE WILL APPEAR.
// ALL LOGS IN THIS FILE WILL BE NULL STATEMENTS WITH NO OVERHEAD.
#define LOG_LEVEL LOG_LEVEL_DISABLED
#include <liblogger/liblogger.h>

int TestFuncNoLogs()
{
	// log the function entry log.
	LogFuncEntry();

	LogTrace("Trace log %s %f", "Test", 1.066f);
	LogDebug("Debug level log" );
	LogInfo("Info level log %d" , 0);
	LogWarn("Warn level log" );
	LogError("Error level log" );
	LogFatal("Fatal level log" );

	if(1)
	{
		// log the function exit .
		LogFuncExit();
		return 0;
	}
	else
	{
		// log the function exit .
		LogFuncExit();
		return -1;
	}
	
}
