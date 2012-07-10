/**
 * \file 
 * Minimalistic usage of liblogger, without bothering 
 * about module name and log level.
 * */
// If you dont want to bother about log levels and module names,
// then the minimum thing that needs to be done is to include the header below
// and start logging. - NOTE LOGS WITH ALL PRIORITY WILL APPEAR IN THIS CASE
#include <liblogger/liblogger.h>

int TestFuncMin()
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
