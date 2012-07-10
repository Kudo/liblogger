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
#ifndef __LOGGER_OBJECT_H__
#define __LOGGER_OBJECT_H__
#include <stdarg.h>
#include <stdio.h>
#include <liblogger/liblogger.h>

/* fwd declaration. */
struct LogWriter;
typedef int (*Log)(struct LogWriter* _this,const LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);
typedef int (*LogFuncEntry)(struct LogWriter * _this,const char* funcName);
typedef int (*LogFuncExit)(struct LogWriter* _this,const char* funcName,int lineNum);
typedef int (*LoggerDeInit)(struct LogWriter* _this);

/** The log writer object */
typedef struct LogWriter
{
	/** Member function to log. */
	Log 			log;
	/** Member function to log the function entry. */
	LogFuncEntry 	logFuncEntry;
	/** Member function to log the function exit. */
	LogFuncExit		logFuncExit;
	/** Member function to deinitialize the log writer object, the log writer object will
	 * not be referenced after this call.*/
	LoggerDeInit	loggerDeInit;
}LogWriter;


#endif // __LOGGER_OBJECT_H__
