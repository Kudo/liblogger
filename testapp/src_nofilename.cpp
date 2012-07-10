/**
 * \file 
 * Sample file illustrating the selective disabling of filename
 * from appearing in the logs generated from this file.
 * */
#include <liblogger/liblogger_levels.h>
// For this file, we choose the logs with priority Info and higher, 
// so logs with lesser priority i.e 
// LogTrace(), LogDebug(), will NOT appear, THEY WILL BE NULL STATEMENTS WITH NO OVERHEAD
#define LOG_LEVEL LOG_LEVEL_INFO
// We Choose not to include the filenames in the log generated from this source file.
#define DISABLE_FILENAMES
// The module name for this file.
#define LOG_MODULE_NAME	"ModuleInfoTest"
#include <liblogger/liblogger.h>

int TestNoFilename()
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
