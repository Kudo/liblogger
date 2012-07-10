/**
 * \file 
 * Sample file illustrating the usage of append mode.
 * */
#include <liblogger/liblogger.h>
#include <liblogger/file_logger.h>
#include <liblogger/socket_logger.h>
#include <memory.h>

void TestLogToFile_Append();
void TestLogFuncs_Append();

int main()
{
	// log to a file in append mode.
	TestLogToFile_Append();
}

void TestLogToFile_Append()
{
	tFileLoggerInitParams fileInitParams;
	// very important, memset to prevent breaks when new members are
	// added to fileInitParams.
	memset(&fileInitParams,0,sizeof(tFileLoggerInitParams));
	fileInitParams.fileName = "log.log";
	fileInitParams.fileOpenMode = AppendMode;
	InitLogger(LogToFile,&fileInitParams);
	TestLogFuncs_Append();
	DeInitLogger();
}

	
void TestLogFuncs_Append()
{
	LogWarn("Warning message......");
	LogDebug(" debug log  %#x", 8909);

	// crash testing, test for buffer overflow vulnerability, in case of socket logging, this huge log
	// will be truncated.
	LogDebug("abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz"
		);

	LogInfo(" Log Info ");
	LogTrace("Log Trace ....... \n");
	LogFatal (" Testing LogFatal.......");

}
