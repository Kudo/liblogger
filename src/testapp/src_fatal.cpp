/**
 * \file 
 * Sample file illustrating the log priority usage.
 * In this file, we choose logs of priority fatal.
 * */
#include <liblogger/liblogger_levels.h>
// For this file, we choose the fatal logs, 
// so logs with lesser priority i.e 
// LogTrace(), LogDebug(), LogInfo(), LogWarn() and LogError() will NOT appear, THEY WILL BE NULL STATEMENTS WITH NO OVERHEAD
#define LOG_LEVEL LOG_LEVEL_FATAL
// The module name for this file.
#define LOG_MODULE_NAME	"ModuleA"
#include <liblogger/liblogger.h>

int TestFuncFatal()
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
