/**
 * \file 
 * Sample file illustrating the log priority usage.
 * In this file, we choose logs of priority warn and higher.
 * */
#include <liblogger/liblogger_levels.h>
// For this file, we choose the Warn level logs, 
// so logs with lesser priority i.e 
// LogTrace(), LogDebug(), LogInfo(), will NOT appear, THEY WILL BE NULL STATEMENTS WITH NO OVERHEAD
#define LOG_LEVEL LOG_LEVEL_WARN
// The module name for this file.
#define LOG_MODULE_NAME	"LogWarnTest"
#include <liblogger/liblogger.h>

int TestFuncWarn()
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
