/**
 * \file 
 * Sample file illustrating the log priority usage.
 * In this file, we choose logs of priority debug or higher
 * */
#include <liblogger/liblogger_levels.h>
// For this file, we choose the logs with priority Debug and higher, 
// so logs with lesser priority i.e 
// LogTrace(), will NOT appear, THEY WILL BE NULL STATEMENTS WITH NO OVERHEAD
#define LOG_LEVEL LOG_LEVEL_DEBUG
// The module name for this file.
#define LOG_MODULE_NAME	"ModuleDebugTest"
#include <liblogger/liblogger.h>

int TestFuncDebug()
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
