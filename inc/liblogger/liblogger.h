/*
       Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
 */
#ifndef __EXP_LOGGER_H__
#define __EXP_LOGGER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <liblogger/liblogger_levels.h>
#include <liblogger/liblogger_config.h>

/** Liblogger major version */
#define LIBLOGGER_MAJOR_VERSION 0
/** Liblogger minor version */
#define LIBLOGGER_MINOR_VERSION 1

/** enum which indicates the log destination, used with \ref InitLogger */
typedef enum LogDest
{
	/** Indicates that logging should be done to file. */
	LogToFile,
	/** Log to Console. (stdout) */
	LogToConsole,
	/** Indicates that logging should be done to socket. Please note that log server should be 
	 *  running. */
	LogToSocket
}LogDest;

/* few compilers dont support variadic macros,so initially undef it, 
 * and depending on the compiler define it.
 */
#undef VARIADIC_MACROS

#if !defined(DISABLE_VARIADIC_CHECK) && (defined(__GNUC__) || (_MSC_VER >= 1400))
	/* 1. GCC supports variadic macros, 
	 * 2. this feature is available only in VS 2005 or higher versions.
	 * */
	#define VARIADIC_MACROS
#endif

/* Forcefully enable the variadic macro support, results in compiler errors if not supported. */
#ifdef ASSUME_VARIADIC_SUPPORT
	#define VARIADIC_MACROS
#endif	


/* WIN32 support. */
#if defined(WIN32) || defined(_WIN32)
#define __func__ __FUNCTION__
#endif

// The logs are enabled.

#ifdef VARIADIC_MACROS	
int LogStub_vm(LogLevel logLevel,
	const char* file, const char* funcName, const int lineNum,
	const char* fmt,...);
#endif
/** 
 * Function used to initialize the logger.
 * \param [in] ldest The log destination. see \ref LogDest for possible destinations.
 * \param [in] loggerInitParams The logger initialization parameters.
 * \returns 0 if successful, -1 if there is a failure.
 * */
int InitLogger(LogDest ldest,void* loggerInitParams);

/** Function used to deinitialize the logger. */
void DeInitLogger();


/* -- Log Level Trace -- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogTrace(fmt, ...) LogStub_vm(Trace,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogTrace(fmt, ...) LogStub_vm(Trace,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Trace level. */
	int LogTrace(const char *fmt, ...);
#endif // VARIADIC_MACROS

/* -- Log Level Debug -- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogDebug(fmt, ...) LogStub_vm(Debug,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogDebug(fmt, ...) LogStub_vm(Debug,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Debug level. */
	int LogDebug(const char *fmt, ...);
#endif // VARIADIC_MACROS

/* -- Log Level Info -- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogInfo(fmt, ...) LogStub_vm(Info,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogInfo(fmt, ...) LogStub_vm(Info,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Info level. */
	int LogInfo(const char *fmt, ...);
#endif // VARIADIC_MACROS

/* -- Log Level Warn -- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogWarn(fmt, ...) LogStub_vm(Warn,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogWarn(fmt, ...) LogStub_vm(Warn,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Warn level. */
	int LogWarn(const char *fmt, ...);
#endif // VARIADIC_MACROS

/* -- Log Level Error-- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogError(fmt, ...) LogStub_vm(Error,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogError(fmt, ...) LogStub_vm(Error,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Error level. */
	int LogError(const char *fmt, ...);
#endif // VARIADIC_MACROS

/* -- Log Level Fatal -- */
#ifdef VARIADIC_MACROS
	#if defined(DISABLE_FILENAMES)
		/* the filename should be disabled. */
		#define LogFatal(fmt, ...) LogStub_vm(Fatal,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#else 
		#define LogFatal(fmt, ...) LogStub_vm(Fatal,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
	#endif // DISABLE_FILENAMES
#else
	/** Emit a log with Fatal level. */
	int LogFatal(const char *fmt, ...);
#endif // VARIADIC_MACROS

#ifdef VARIADIC_MACROS
	/* Log Entry to a function. */
	int FuncLogEntry(const char* funcName);
	/* Log return from a function. */
	int FuncLogExit(const char* funcName,const int lineNumber);
	
	#define LogFuncEntry()	FuncLogEntry(__func__)
	#define LogFuncExit()	FuncLogExit(__func__,__LINE__)
#else
	#define LogFuncEntry()	    /*NOP*/
	#define LogFuncExit()	    /*NOP*/
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EXP_LOGGER_H__ */

